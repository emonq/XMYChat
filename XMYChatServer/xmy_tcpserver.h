#ifndef XMY_TCPSERVER_H
#define XMY_TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostInfo>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>


#define TYPE_LOGIN 0
#define TYPE_REGISTER 1

#define LOGIN_STATUS int
#define LOGIN_SUCCESS 0
#define LOGIN_INFO_ERROR 1
#define LOGIN_CONNECTION_ERROR 2
#define LOGIN_USER_NOT_FOUND 3
#define LOGIN_USER_BANNED 4

class Q_tcpserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit Q_tcpserver(QObject *parent=Q_NULLPTR);
    QList<QHostAddress> get_addr();
    void stop_server();
    ~Q_tcpserver();

signals:
    void receive_message(QString msg);
    void new_log(QString msg);

private:

    QList<QTcpSocket*> clients;

    int authentication(QJsonObject login_info);


private slots:
    void establish_connection();
    void slot_read_message();
};

#endif // XMY_TCPSERVER_H
