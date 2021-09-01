#ifndef XMY_TCPSOCKET_H
#define XMY_TCPSOCKET_H

#include <QTcpSocket>
#include <QObject>

#include "xmy_basic.h"

class XMY_tcpsocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit XMY_tcpsocket(QObject *parent = nullptr);
    XMY_tcpsocket(qintptr socketDescriptor, QUuid socketId);
    void send_json(QJsonObject data);
    QUuid id;

signals:
    void receive_json(QJsonObject data);

private slots:
    void slot_ready_read();

};

#endif // XMY_TCPSOCKET_H
