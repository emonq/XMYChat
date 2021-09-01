#include "loginsession.h"

loginsession::loginsession(QObject *parent) : QObject(parent)
{
    socket=new XMY_tcpsocket;
    settings=new xmyUserSettings;
    connect(this,&loginsession::connection_error,this,&loginsession::slot_connection_error);
    connect(socket,&XMY_tcpsocket::disconnected,this,&loginsession::sig_logout);
    establish_connect();
}

loginsession::~loginsession()
{
    delete settings;
    delete socket;
}

void loginsession::user_login(QString email, QString password)
{
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        emit general_return(CONNECTION_ERROR);
        emit connection_error();
        return;
    }
    QJsonObject login_info;
    login_info.insert("type",TYPE_LOGIN);
    QString hash_password=QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex();
    login_info.insert("email",email);
    login_info.insert("password",hash_password);
    info["email"]=email;
    socket->send_json(login_info);
}

bool loginsession::user_register(QString email, QString password, QString username)
{
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        emit general_return(CONNECTION_ERROR);
        emit connection_error();
        return false;
    }
    info["email"]=email;
    QJsonObject user_info;
    user_info.insert("type",TYPE_REGISTER);
    QString hash_password=QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex();
    user_info.insert("email",email);
    user_info.insert("password",hash_password);
    user_info.insert("username",username);
    QJsonDocument data(user_info);
    socket->write(data.toJson(QJsonDocument::Compact));
    return true;
}

void loginsession::establish_connect()
{
    socket->disconnectFromHost();
    socket=new XMY_tcpsocket;
    connect(socket,&XMY_tcpsocket::connected,this,&loginsession::slot_connected);
    connect(socket,&XMY_tcpsocket::disconnected,this,&loginsession::slot_disconnected);
    connect(socket,&XMY_tcpsocket::receive_json,this,&loginsession::callback_process);
    qDebug()<<"connecting";
    QVariant ip, port;
    settings->get_value("Server ip",ip);
    settings->get_value("Server port", port);
    socket->connectToHost(ip.toString(), port.toInt());
    return;
}

void loginsession::logout()
{
    QJsonObject data;
    data.insert("type",TYPE_LOGOUT);
    socket->send_json(data);
    emit sig_logout();
}

void loginsession::send_message(QString to_email, QString msg)
{
    QJsonObject data;
    data.insert("type",TYPE_SEND_MESSAGE);
    data.insert("email",info["email"]);
    data.insert("to_email",to_email);
    data.insert("message",msg);
    socket->send_json(data);
    db->append_message(to_email,msg,XMY_Utilities::get_time_string(),info.value("email"));
}

void loginsession::email_verify(int code)
{
    QJsonObject data;
    data.insert("type",TYPE_VERIFY);
    data.insert("code",code);
    data.insert("email",info["email"]);
    socket->send_json(data);
}

void loginsession::user_info_modify(QJsonObject data)
{
    socket->send_json(data);
}

void loginsession::get_user_info(QString email)
{
    if(email.isEmpty()) email=info["email"];
    QJsonObject data;
    data.insert("type",TYPE_GET_USER_INFO);
    data.insert("email",email);
    socket->send_json(data);
}

void loginsession::fetch_friend_list()
{
    QJsonObject data;
    data.insert("type",TYPE_FETCH_FRIEND_LIST);
    data.insert("email",info["email"]);
    socket->send_json(data);
}

void loginsession::get_avatar(QString email, QString md5)
{
    if(email.isEmpty()) email=info["email"];
    QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
    QJsonObject data;
    if(QFile(filename).exists()){
        QPixmap pic(filename);
        QString picmd5=XMY_Utilities::pixmaptomd5(pic);
//        qDebug()<<email<<filename<<"cache md5: "<<picmd5<<" remote md5: "<<md5;
        if(picmd5==md5) return;
        data.insert("md5",picmd5);
    }
    data.insert("type",TYPE_GET_AVATAR);
    data.insert("email",email);
    socket->send_json(data);
}

void loginsession::search_user(QString email)
{
    QJsonObject data;
    data.insert("type",TYPE_SEARCH_USER);
    data.insert("email",email);
    socket->send_json(data);
}

void loginsession::add_user(QString email)
{
    QJsonObject data;
    data.insert("type",TYPE_ADD_FRIEND);
    data.insert("email1",email);
    data.insert("email2",info.value("email"));
    socket->send_json(data);
}

void loginsession::delete_user(QString email)
{
    QJsonObject data;
    data.insert("type",TYPE_DELETE_FRIEND);
    data.insert("email1",email);
    data.insert("email2",info.value("email"));
    db->delete_friend(email);
    socket->send_json(data);
}

QList<chatMessage> loginsession::get_messages_by_email(QString email)
{
    QList<chatMessage> msg;
    db->get_messages_by_email(email,msg);
    return msg;
}

void loginsession::callback_process(QJsonObject data)
{
//    qDebug()<<data;
    switch (data.value("type").toInt()) {
    case TYPE_LOGIN: {
        if(data.value("result").toInt()==LOGIN_SUCCESS) {
            info["username"]=data.value("username").toString();
            db=new ClientDatabase(this,info.value("email"));
        }
        emit login_return(data.value("result").toInt());
        break;
    }
    case TYPE_REGISTER: {
        emit register_return(data.value("result").toInt());
        break;
    }
    case TYPE_SEND_MESSAGE: {
        if(data.value("result").toBool()==false) emit send_message_failed();
        break;
    }
    case TYPE_RECEIVE_MESSAGE: {
        chatMessage msg(data.value("from_email").toString(),data.value("time").toString(),data.value("message").toString());
        db->append_message(data.value("from_email").toString(),data.value("message").toString(),data.value("time").toString(),data.value("from_email").toString());
        emit sig_receive_message(msg);
        break;
    }
    case TYPE_GET_USER_INFO: {
        info["username"]=data.value("username").toString();
        info["avatar"]=data.value("avatar").toString();
        emit info_refreshed();
        break;
    }
    case TYPE_FETCH_FRIEND_LIST: {
        friend_email_list.clear();
        friends.clear();
        for(auto i:data.value("list").toArray()) {
            friend_email_list.append(i.toObject().value("email").toString());
            friends.append(userStruct(i.toObject().value("username").toString(),i.toObject().value("email").toString(),i.toObject().value("avatarmd5").toString()));
            get_avatar(i.toObject().value("email").toString(),i.toObject().value("avatarmd5").toString());
            db->add_friend(i.toObject().value("email").toString());
        }
        emit friend_list_refreshed();
        break;
    }
    case TYPE_SEARCH_USER: {
        if(data.value("count").toInt()>0) {
            userStruct user(data.value("username").toString(),data.value("email").toString(),data.value("avatarmd5").toString());
            get_avatar(data.value("email").toString(),data.value("avatarmd5").toString());
            emit user_found(user);
        }
        else emit user_not_found();
        break;
    }
    case TYPE_GET_AVATAR: {
        if(data.value("result").toInt()==GET_AVATAR_OK) {
            if(XMY_Utilities::checkDir(".cache")){
                QString filename=XMY_Utilities::get_avatar_filename(".cache\\",data.value("email").toString());
//                QString filename=".cache\\"+XMY_Utilities::emailtomd5(data.value("email").toString())+".png";
                XMY_Utilities::save_pic_from_base64(data.value("avatar").toString(),filename);
                emit avatar_got(data.value("email").toString());
            }
        }
        break;
    }
    default: emit general_return(data.value("result").toInt());
    }
}

void loginsession::slot_connection_error()
{
    establish_connect();
}

void loginsession::slot_connected()
{
    emit general_return(CONNECTION_CONNECTED);
    qDebug()<<"connected";
}


void loginsession::slot_disconnected()
{
    qDebug("disconnected");
    emit general_return(CONNECTION_ERROR);
    emit sig_logout();
    socket->deleteLater();
}
