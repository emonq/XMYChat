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
    if(!XMY_Utilities::check_valid_email(email)) {
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
                if(loginusers.contains(login_info.value("email").toString())) clients.value(loginusers.value(login_info.value("email").toString()))->disconnectFromHost();
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
    if(!XMY_Utilities::check_valid_email(email)) {
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
//    QNetworkAccessManager* networkmanager = new QNetworkAccessManager();
//    connect(networkmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleEndOfRequest(QNetworkReply*)));
    XMY_tcpsocket* socket=clients.value(loginusers.value(to_email));
    if(socket==NULL) return false;
    QJsonObject data;
    data.insert("type",TYPE_RECEIVE_MESSAGE);
    data.insert("from_email",from_email);
    data.insert("message",msg);
    data.insert("time",XMY_Utilities::get_time_string());
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
    params.addQueryItem("html", QString("<p>Your verification code is:</p><h1>%1</h1>").arg(code));
    params.addQueryItem("subject", "XMYChat email verification");
    networkmanager->post(send_request, params.toString().toUtf8());
    emit new_log(QString("Sent verification code %1 to %2").arg(code).arg(email));
}


bool XMY_tcpserver::fetch_friend_list(QString email, QJsonObject& ret)
{
    QMap<QString,QVariant> info;
    if(db->get_user_by_email(email, info, "u_friends")!=SUCCESS) {
        return false;
    }
    QStringList friends=info["u_friends"].toString().split(";", Qt::SkipEmptyParts);
    ret.insert("count",friends.count());
    QJsonArray friends_array;
    for(auto &i:friends) {
        QJsonObject tmp;
        QMap<QString,QVariant> friend_info;
        db->get_user_by_email(i,friend_info,"u_username");
        tmp.insert("email",i);
        tmp.insert("username",friend_info["u_username"].toString());
        QString avatar_file=XMY_Utilities::get_avatar_filename(".avatar\\",i);
        if(!QFile(avatar_file).exists()) avatar_file=".avatar\\default.png";
        tmp.insert("avatarmd5",XMY_Utilities::pixmaptomd5(QPixmap(avatar_file)));
        friends_array.append(tmp);
    }
    ret.insert("list",friends_array);
    return true;
}

void XMY_tcpserver::search_user(QString email, QJsonObject &ret)
{
    QMap<QString, QVariant> info;
    ret.insert("type",TYPE_SEARCH_USER);
    if(db->get_user_by_email(email,info,"u_username")==RECORD_NOT_FOUND) {
        ret.insert("count",0);
        return;
    }
    ret.insert("count",1);
    ret.insert("email",email);
    ret.insert("username",info.value("u_username").toString());
    ret.insert("avatarmd5",XMY_Utilities::pixmaptomd5(QPixmap(XMY_Utilities::get_avatar_filename(".avatar\\",email))));
}

void XMY_tcpserver::add_friend(QString email1, QString email2)
{
    QMap<QString,QVariant> info;
    db->get_user_by_email(email1,info,"u_friends");
    QString friend_list=info.value("u_friends").toString();
    friend_list.append(email2+';');
    db->set_user_by_email(email1,"u_friends",friend_list);
}

void XMY_tcpserver::delete_friend(QString email1, QString email2)
{
    QMap<QString, QVariant> info;
    db->get_user_by_email(email1,info,"u_friends");
    QStringList friend_list=info.value("u_friends").toString().split(';',Qt::SkipEmptyParts);
    friend_list.remove(friend_list.indexOf(email2));
    db->set_user_by_email(email1,"u_friends",friend_list.join(';')+';');
}

void XMY_tcpserver::update_friend_list(QString email)
{
    XMY_tcpsocket* socket=clients.value(loginusers.value(email));
    if(socket==NULL) return;
    QJsonObject data;
    data.insert("type",TYPE_FETCH_FRIEND_LIST);
    fetch_friend_list(email,data);
    socket->send_json(data);
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
    case TYPE_INFO_MODIFY: {
        QString email=req.value("email").toString();
        for(auto &i:req.keys()) {
            if(i=="avatar") XMY_Utilities::save_pic_from_base64(req.value(i).toString(),".avatar\\"+XMY_Utilities::emailtomd5(email)+".png");
            else if(i=="email") {
                if(XMY_Utilities::check_valid_email(req.value(i).toString()))
                    db->set_user_by_email(email,"u_email",req.value(i));
            }
            else if(i=="username") db->set_user_by_email(email,"u_username",req.value(i));
        }
        break;
    }
    case TYPE_GET_USER_INFO: {
        QMap<QString,QVariant> info;
        db->get_user_by_email(req.value("email").toString(),info,"u_username");;
        ret.insert("type",TYPE_GET_USER_INFO);
        ret.insert("username",info.value("u_username").toString());
        break;
    }
    case TYPE_GET_AVATAR: {
        XMY_Utilities::checkDir(".avatar");
        QString filename=".avatar\\"+XMY_Utilities::emailtomd5(req.value("email").toString())+".png";
        if(!QFile(filename).exists()) filename=".avatar\\default.png";
        ret.insert("type",TYPE_GET_AVATAR);
        ret.insert("email",req.value("email").toString());
        if(XMY_Utilities::pixmaptomd5(QPixmap(filename))==req.value("md5").toString()) {
            ret.insert("result",GET_AVATAR_NOCHANGE);
        }
        else {
            ret.insert("result",GET_AVATAR_OK);
            ret.insert("avatar",XMY_Utilities::get_pic_base64(filename));
        }
        break;
    }
    case TYPE_FETCH_FRIEND_LIST: {
        ret.insert("type",TYPE_FETCH_FRIEND_LIST);
        fetch_friend_list(req.value("email").toString(),ret);
        break;
    }
    case TYPE_SEARCH_USER: {
        search_user(req.value("email").toString(),ret);
        break;
    }
    case TYPE_ADD_FRIEND: {
        add_friend(req.value("email1").toString(),req.value("email2").toString());
        add_friend(req.value("email2").toString(),req.value("email1").toString());
        update_friend_list(req.value("email1").toString());
        update_friend_list(req.value("email2").toString());
        break;
    }
    case TYPE_DELETE_FRIEND: {
        delete_friend(req.value("email1").toString(),req.value("email2").toString());
        delete_friend(req.value("email2").toString(),req.value("email1").toString());
        update_friend_list(req.value("email1").toString());
        update_friend_list(req.value("email2").toString());
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
