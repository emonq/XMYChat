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
//        clients.remove(*i);
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

int XMY_tcpserver::user_authentication(QJsonObject login_info)
{
    QString username=login_info.value("username").toString().toUtf8().toBase64();
    QString password=login_info.value("password").toString().toUtf8().toBase64();
    QMap<QString,QVariant> res;
    int ret_code=db->get_user_by_username(username, res, "u_password,is_banned");
    if(ret_code==RECORD_NOT_FOUND) return LOGIN_USER_NOT_FOUND;
    if(ret_code) return ret_code;
    if(res.value("u_password")==password) {
        if(res.value("is_banned").toInt()==1) return LOGIN_USER_BANNED;
        return LOGIN_SUCCESS;
    }
    return LOGIN_INFO_ERROR;
}

int XMY_tcpserver::user_create(QJsonObject user_info)
{
    QString username=user_info.value("username").toString().toUtf8().toBase64();
    QString password=user_info.value("password").toString().toUtf8().toBase64();
    if(db->new_user(username,password)) return REGISTER_SUCCESS;
    else return REGISTER_USER_EXISTED;
}

void XMY_tcpserver::request_process(QJsonObject req)
{

    QJsonObject ret;
    XMY_tcpsocket* socket=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("From [%1]:%2 %3: ").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socket->socketDescriptor())+QJsonDocument(req).toJson(QJsonDocument::Compact));
    switch(req.value("type").toInt()){
    case TYPE_LOGIN: {
        ret.insert("type",TYPE_LOGIN);
        ret.insert("result",user_authentication(req));
        break;
    }
    case TYPE_REGISTER: {
        ret.insert("type",TYPE_REGISTER);
        ret.insert("result",user_create(req));
        break;
    }
    default: {
        ret.insert("result",REQUEST_ERROR);
        break;
    }
    }
    emit new_log(QJsonDocument(ret).toJson(QJsonDocument::Compact));
    socket->send_json(ret);
}

void XMY_tcpserver::slot_disconnected()
{
    XMY_tcpsocket* client=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("[%1]:%2 %3 disconnected.").arg(client->peerAddress().toString()).arg(client->peerPort()).arg(client->id));
//    qintptr socketDescriptor=client->socketDescriptor();
    clients.remove(client->id);
    client->deleteLater();
}
