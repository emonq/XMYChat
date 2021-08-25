#include "xmy_tcpserver.h"



Q_tcpserver::Q_tcpserver(QObject *parent)
{
    connect(this,&Q_tcpserver::newConnection,this,&Q_tcpserver::establish_connection);
}

QList<QHostAddress> Q_tcpserver::get_addr()
{
    QList<QHostAddress> ip;
    QString hostname;
    QHostInfo hostinfo;
    hostname=QHostInfo::localHostName();
    hostinfo=QHostInfo::fromName(hostname);
    ip=hostinfo.addresses();
    return ip;
}

void Q_tcpserver::stop_server()
{
    close();
    for(auto& i:clients) {
        i->disconnectFromHost();
        if(i->state()!=QAbstractSocket::UnconnectedState) {
            i->abort();
        }
    }
}

Q_tcpserver::~Q_tcpserver()
{
    stop_server();
}

int Q_tcpserver::authentication(QJsonObject login_info)
{

}


void Q_tcpserver::establish_connection()
{

    QTcpSocket*socket=nextPendingConnection();
    clients.append(socket);
    connect(socket,&QTcpSocket::readyRead,this,&Q_tcpserver::slot_read_message);
    emit new_log(QString("New connection from %1 at port %2").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
}

void Q_tcpserver::slot_read_message()
{
    QTcpSocket *client=qobject_cast<QTcpSocket*>(sender());
    QByteArray buf=client->readAll();
    QString msg=QString("From [%1]: %2").arg(client->peerAddress().toString()).arg(buf);
    emit receive_message(msg);
}


