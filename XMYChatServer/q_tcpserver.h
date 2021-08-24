#ifndef Q_TCPSERVER_H
#define Q_TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostInfo>
//#include <QTcpSocket>

class Q_tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit Q_tcpserver(QObject *parent = nullptr);
    QList<QHostAddress> get_addr();
    void start_server(QHostAddress ip, int port);
    void stop_server();

signals:

private:
    QList<QHostAddress> ip;
    QString hostname;
    QHostInfo hostinfo;

    QTcpServer *tcpserver;
//    QList<QTcpSocket> tcpsockets;

    void get_network_info();

};

#endif // Q_TCPSERVER_H
