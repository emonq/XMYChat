#ifndef LOGINSESSION_H
#define LOGINSESSION_H

#define SERVER_ADDR QString("127.0.0.1")
#define SERVER_PORT 42000

#define TYPE_LOGIN 0
#define TYPE_REGISTER 1

#define LOGIN_STATUS int
#define LOGIN_SUCCESS 0
#define LOGIN_INFO_ERROR 1
#define LOGIN_CONNECTION_ERROR 2
#define LOGIN_USER_NOT_FOUND 3
#define LOGIN_USER_BANNED 4


#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class loginsession : public QObject
{
    Q_OBJECT
public:
    explicit loginsession(QObject *parent = nullptr);
    LOGIN_STATUS login(QString username, QString password);


signals:

private:
    QTcpSocket *socket;
    void establish_connect();
private slots:
    void slot_connected();
    void slot_receive_message();
    void slot_disconnected();
};

#endif // LOGINSESSION_H
