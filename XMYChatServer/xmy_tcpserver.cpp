#include "xmy_tcpserver.h"



XMY_tcpserver::XMY_tcpserver(QObject *parent) : QTcpServer(parent)
{
    db=new XMY_database;
    connect(db,&XMY_database::new_log,this,&XMY_tcpserver::new_log);
}

QList<QHostAddress> XMY_tcpserver::get_addr()
{
    QList<QHostAddress> ip;
    QString hostname;
    QHostInfo hostinfo;
    hostname=QHostInfo::localHostName();
    hostinfo=QHostInfo::fromName(hostname);
    ip=hostinfo.addresses();
    return ip;
}

bool XMY_tcpserver::start_server(QHostAddress ip, int port)
{
//    send_verification_code("emonq@outlook.com");
    bool listen_status=listen(ip,port);
    bool connect_status=db->connect_db();
    if(listen_status && connect_status) {
        return true;
    }
    else if(!connect_status){
        if(db->init_db() && db->connect_db()) return true;
        else if(listen_status) stop_server();
    }
    return false;
}

void XMY_tcpserver::stop_server()
{
    close();
    for(auto i=clients.keyBegin();i!=clients.keyEnd();i++) {
        emit new_log(QString("Disconnecting [%1]:%2 %3").arg(clients[*i]->peerAddress().toString()).arg(clients[*i]->peerPort()).arg(clients[*i]->socketDescriptor()));
        clients[*i]->disconnectFromHost();
    }
    db->disconnect_db();
}


XMY_tcpserver::~XMY_tcpserver()
{
    stop_server();
    delete db;
}

void XMY_tcpserver::incomingConnection(qintptr socketDescriptor)
{
    XMY_tcpsocket* socket=new XMY_tcpsocket(socketDescriptor);
    clients.insert(socketDescriptor,socket);
    connect(socket,&XMY_tcpsocket::receive_json,this,&XMY_tcpserver::request_process);
    connect(socket,&XMY_tcpsocket::disconnected,this,&XMY_tcpserver::slot_disconnected);
    emit new_log(QString("New connection from [%1]:%2 %3.").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socketDescriptor));
}

void XMY_tcpserver::user_authentication(QJsonObject login_info, QJsonObject& ret_data, qintptr socketDescriptor)
{
    QString email=login_info.value("email").toString();
    if(!check_valid_email(email)) {
        ret_data.insert("result",LOGIN_INFO_ERROR);
        return;
    }
    QString password=login_info.value("password").toString().toUtf8().toBase64();
    QMap<QString,QVariant> res;
    int result;
    int ret_code=db->get_user_by_email(email, res, "u_password,is_banned,is_waiting_verification");
    if(ret_code==RECORD_NOT_FOUND) result=LOGIN_USER_NOT_FOUND;
    else if(ret_code) result=ret_code;
    else {
        if(res.value("u_password")==password) {
            if(res.value("is_banned").toInt()==1) result=LOGIN_USER_BANNED;
            else if(res.value("is_waiting_verification").toInt()==1) result=LOGIN_USER_WAITING_VERIFICATION;
            else {
                result=LOGIN_SUCCESS;
                loginusers.insert(login_info.value("email").toString(),socketDescriptor);
            }
        }
        else result=LOGIN_INFO_ERROR;
    }
    ret_data.insert("result",result);
}

void XMY_tcpserver::user_create(QJsonObject user_info, QJsonObject& ret_data)
{
    int result;
    QString email=user_info.value("email").toString();
    QString password=user_info.value("password").toString().toUtf8().toBase64();
    if(!check_valid_email(email)) {
        ret_data.insert("result",REGISTER_INFO_ERROR);
        return;
    }
    if(db->new_user(email,password)) {
        result=REGISTER_WAITING_VERIFICATION;
        send_verification_code(email);
    }
    else result=REGISTER_USER_EXISTED;
    ret_data.insert("result",result);
}

bool XMY_tcpserver::send_message(QString from_email, QString to_email, QString msg)
{
    QNetworkAccessManager* networkmanager = new QNetworkAccessManager();
    connect(networkmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleEndOfRequest(QNetworkReply*)));
    XMY_tcpsocket* socket=clients.value(loginusers.value(to_email));
    QJsonObject data;
    data.insert("type",TYPE_RECEIVE_MESSAGE);
    data.insert("from_email",from_email);
    data.insert("message",msg);
    data.insert("time",QDateTime::currentDateTime().toString("hh:mm:ss yyyy.MM.dd"));
    emit new_log(QJsonDocument(data).toJson(QJsonDocument::Compact));
    socket->send_json(data);
    return true;
}

bool XMY_tcpserver::email_verify(QString email, int code, QJsonObject& ret_data)
{
    QMap<QString,QVariant> info;
    db->get_user_by_email(email, info, "u_verification_code,is_waiting_verification");
    if(info.value("is_waiting_verification").toInt()) {
        if(info.value("u_verification_code").toInt()==code) {
            ret_data.insert("result",REGISTER_SUCCESS);
            db->set_user_by_email(email,"is_waiting_verification",0);
        }
        else {
            ret_data.insert("result",REGISTER_WAITING_VERIFICATION);
        }
        return true;
    }
    else {
        ret_data.insert("result",REGISTER_SUCCESS);
        return false;
    }
}

void XMY_tcpserver::send_verification_code(QString email)
{
    int code=QRandomGenerator::global()->bounded(10000,99999);
    db->set_user_by_email(email,"is_waiting_verification",1);
    db->set_user_by_email(email,"u_verification_code",code);
    QUrl resource("https://api.mailgun.net/v3/send.emonq.com/messages");
    QNetworkRequest send_request(resource);
    send_request.setRawHeader("Authorization",MAILGUN_KEY);
    send_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkAccessManager* networkmanager = new QNetworkAccessManager();
    connect(networkmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleEndOfRequest(QNetworkReply*)));
    QUrlQuery params;
    params.addQueryItem("from", "xmychat@send.emonq.com");
    params.addQueryItem("to", email);
    params.addQueryItem("html", QString("<h1>Your verification code is:</h1><p>%1</p>").arg(code));
    params.addQueryItem("subject", "XMYChat email verification");
    networkmanager->post(send_request, params.toString().toUtf8());
    emit new_log(QString("Sent verification code %1 to %2").arg(code).arg(email));
}

bool XMY_tcpserver::check_valid_email(QString email)
{
    QRegularExpression re("[a-zA-z0-9]+\\@[a-zA-z0-9]+\\.[a-zA-z0-9]+");
    return re.match(email).hasMatch();
}

void XMY_tcpserver::request_process(QJsonObject req)
{
    QJsonObject ret;
    XMY_tcpsocket* socket=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("From [%1]:%2 %3: ").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socket->socketDescriptor())+QJsonDocument(req).toJson(QJsonDocument::Compact));
    switch(req.value("type").toInt()){
    case TYPE_LOGIN: {
        ret.insert("type",TYPE_LOGIN);
        user_authentication(req,ret,socket->socketDescriptor());
        break;
    }
    case TYPE_REGISTER: {
        ret.insert("type",TYPE_REGISTER);
        user_create(req,ret);
        break;
    }
    case TYPE_LOGOUT: {
        loginusers.remove(req.value("email").toString());
        return;
    }
    case TYPE_SEND_MESSAGE: {
        ret.insert("type",TYPE_SEND_MESSAGE);
        ret.insert("result",send_message(req.value("email").toString(),req.value("to_email").toString(),req.value("message").toString()));
        break;
    }
    case TYPE_VERIFY: {
        ret.insert("type",TYPE_REGISTER);
        email_verify(req.value("email").toString(),req.value("code").toInt(),ret);
        break;
    }
    default: {
        return;
    }
    }
    emit new_log(QJsonDocument(ret).toJson(QJsonDocument::Compact));
    socket->send_json(ret);
}

void XMY_tcpserver::handleEndOfRequest(QNetworkReply *reply)
{
    emit new_log(reply->readAll());
    QNetworkAccessManager* manager=qobject_cast<QNetworkAccessManager*>(sender());
    manager->deleteLater();
}

void XMY_tcpserver::slot_disconnected()
{
    XMY_tcpsocket* client=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("[%1]:%2 %3 disconnected.").arg(client->peerAddress().toString()).arg(client->peerPort()).arg(client->id));
    clients.remove(client->id);
    client->deleteLater();
}
