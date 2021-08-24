#include "q_tcpserver.h"

Q_tcpserver::Q_tcpserver(QObject *parent) : QObject(parent)
{

}

QList<QHostAddress> Q_tcpserver::get_addr()
{
    get_network_info();
    return ip;
}

void Q_tcpserver::start_server(QHostAddress ip, int port)
{
    tcpserver=new QTcpServer;
    tcpserver->listen(ip,port);
}

void Q_tcpserver::stop_server()
{
    tcpserver->close();
    delete tcpserver;
}

void Q_tcpserver::get_network_info()
{
    hostname=QHostInfo::localHostName();
    hostinfo=QHostInfo::fromName(hostname);
    ip=hostinfo.addresses();
}

