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

void loginsession::user_login(QString username, QString password)
{
    qDebug()<<socket->state();
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        emit general_return(CONNECTION_ERROR);
        emit connection_error();
        return;
    }
    if(!socket->waitForConnected()) return;
    QJsonObject login_info;
    login_info.insert("type",TYPE_LOGIN);
    QString hash_username=QCryptographicHash::hash(username.toUtf8(), QCryptographicHash::Sha384).toHex();
    QString hash_password=QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex();
    login_info.insert("username",hash_username);
    login_info.insert("password",hash_password);
    socket->send_json(login_info);
}

void loginsession::user_register(QString username, QString password)
{
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        emit general_return(CONNECTION_ERROR);
        emit connection_error();
        return;
    }
    QJsonObject user_info;
    user_info.insert("type",TYPE_REGISTER);
    QString hash_username=QCryptographicHash::hash(username.toUtf8(), QCryptographicHash::Sha384).toHex();
    QString hash_password=QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex();
    user_info.insert("username",hash_username);
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

void loginsession::callback_process(QJsonObject data)
{
    qDebug()<<data;
    switch (data.value("type").toInt()) {
    case TYPE_LOGIN: emit login_return(data.value("result").toInt()); break;
    case TYPE_REGISTER: emit register_return(data.value("result").toInt()); break;
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
}


void loginsession::slot_disconnected()
{
    qDebug("disconnected");
    emit general_return(CONNECTION_ERROR);
//    delete socket;
}
