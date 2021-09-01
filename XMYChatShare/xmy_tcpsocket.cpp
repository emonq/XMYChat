#include "xmy_tcpsocket.h"

XMY_tcpsocket::XMY_tcpsocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this,&XMY_tcpsocket::readyRead,this,&XMY_tcpsocket::slot_ready_read);
    setSocketOption(QAbstractSocket::LowDelayOption,1);
}

XMY_tcpsocket::XMY_tcpsocket(qintptr socketDescriptor, QUuid socketId)
{
    id=socketId;
    setSocketDescriptor(socketDescriptor);
    connect(this,&XMY_tcpsocket::readyRead,this,&XMY_tcpsocket::slot_ready_read);
}

void XMY_tcpsocket::send_json(QJsonObject data)
{
    QByteArray rawdata=QJsonDocument(data).toJson(QJsonDocument::Compact);
    write(rawdata);
}

void XMY_tcpsocket::slot_ready_read()
{
    QByteArray rawdata=readAll();
    while(QJsonDocument::fromJson(rawdata).isNull()) { // 解决大数据接收问题
        if(!waitForReadyRead(10)) break;
        rawdata.append(readAll());
    }
//    qDebug()<<rawdata;
    if(QJsonDocument::fromJson(rawdata).isNull()){ // 解决粘包问题
        qsizetype pos;
        QByteArray data;
        while((pos=rawdata.lastIndexOf("}{"))!=-1) {
            data=rawdata.sliced(pos+1);
//            qDebug()<<"splited "<<data;
            rawdata.truncate(pos+1);
            emit receive_json(QJsonDocument::fromJson(data).object());
        }
    }
    emit receive_json(QJsonDocument::fromJson(rawdata).object());
}
