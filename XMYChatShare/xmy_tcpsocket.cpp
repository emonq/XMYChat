#include "xmy_tcpsocket.h"

XMY_tcpsocket::XMY_tcpsocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this,&XMY_tcpsocket::readyRead,this,&XMY_tcpsocket::slot_ready_read);
}

XMY_tcpsocket::XMY_tcpsocket(qintptr socketDescriptor)
{
    setSocketDescriptor(socketDescriptor);
    id=socketDescriptor;
    connect(this,&XMY_tcpsocket::readyRead,this,&XMY_tcpsocket::slot_ready_read);
}

void XMY_tcpsocket::send_json(QJsonObject data)
{
    QByteArray buf=QJsonDocument(data).toJson(QJsonDocument::Compact);
    write(buf);
}

void XMY_tcpsocket::slot_ready_read()
{
    QByteArray buf=readAll();
    QJsonObject data=QJsonDocument::fromJson(buf).object();
    emit receive_json(data);
}