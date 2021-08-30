#include "loginsession.h"

loginsession::loginsession(QObject *parent) : QObject(parent)
{
    socket=new XMY_tcpsocket;
    settings=new xmyUserSettings;
    connect(this,&loginsession::connection_error,this,&loginsession::slot_connection_error);

    establish_connect();
}

loginsession::~loginsession()
{
    delete settings;
    delete socket;
}

void loginsession::user_login(QString email, QString password)
{
    qDebug()<<socket->state();
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
    this->email=email;
    socket->send_json(login_info);
}

void loginsession::user_register(QString email, QString password)
{
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        emit general_return(CONNECTION_ERROR);
        emit connection_error();
        return;
    }
    this->email=email;
    QJsonObject user_info;
    user_info.insert("type",TYPE_REGISTER);
    QString hash_password=QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex();
    user_info.insert("email",email);
    user_info.insert("password",hash_password);
    QJsonDocument data(user_info);
    socket->write(data.toJson(QJsonDocument::Compact));
}

void loginsession::establish_connect()
{
    socket->deleteLater();
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
    qDebug()<<token;
    QJsonObject data;
    data.insert("type",TYPE_LOGOUT);
    data.insert("token",token);
    socket->send_json(data);
    emit sig_logout();
}

void loginsession::send_message(QString to_email, QString msg)
{
    QJsonObject data;
    data.insert("type",TYPE_SEND_MESSAGE);
    data.insert("email",email);
    data.insert("to_email",to_email);
    data.insert("message",msg);
    socket->send_json(data);
}

void loginsession::email_verify(int code)
{
    QJsonObject data;
    data.insert("type",TYPE_VERIFY);
    data.insert("code",code);
    data.insert("email",email);
    socket->send_json(data);
}

void loginsession::callback_process(QJsonObject data)
{
    qDebug()<<data;
    switch (data.value("type").toInt()) {
    case TYPE_LOGIN: {
        token=data.value("token").toString();
        emit login_return(data.value("result").toInt());
        break;
    }
    case TYPE_REGISTER: emit register_return(data.value("result").toInt()); break;
    case TYPE_SEND_MESSAGE: {
        if(data.value("error")==INVALID_TOKEN) emit sig_logout();
        break;
    }
    case TYPE_RECEIVE_MESSAGE: {
        emit sig_receive_message(QString("%1 [%2]").arg(data.value("from_username").toString(),data.value("time").toString()),data.value("message").toString());
    }
    case TYPE_VERIFY:
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
//    delete socket;
}
