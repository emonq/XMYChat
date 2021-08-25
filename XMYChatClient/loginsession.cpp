#include "loginsession.h"

loginsession::loginsession(QObject *parent) : QObject(parent)
{
    socket=new QTcpSocket;
    establish_connect();
}

LOGIN_STATUS loginsession::login(QString username, QString password)
{
    if(socket->state()!=QAbstractSocket::ConnectedState) {
        establish_connect();
        return LOGIN_CONNECTION_ERROR;
    }
    QJsonObject login_info;
    login_info.insert("type",TYPE_LOGIN);
    login_info.insert("username",username);
    login_info.insert("password",password);
    QJsonDocument data(login_info);
    socket->write(data.toJson());
    return LOGIN_SUCCESS;
}

void loginsession::establish_connect()
{
    socket->connectToHost(SERVER_ADDR, SERVER_PORT);
    connect(socket,&QTcpSocket::connected,this,&loginsession::slot_connected);
    connect(socket,&QTcpSocket::readyRead,this,&loginsession::slot_receive_message);
}

void loginsession::slot_connected()
{
    qDebug("connected");
}

void loginsession::slot_receive_message()
{
    QByteArray buf=socket->readAll();
    qDebug()<<buf;
}

void loginsession::slot_disconnected()
{
    qDebug("disconnected");
    socket->close();
}
