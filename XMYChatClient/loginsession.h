#ifndef LOGINSESSION_H
#define LOGINSESSION_H

#include <QObject>
#include <QTcpSocket>

#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "xmyusersettings.h"

class loginsession : public QObject
{
    Q_OBJECT
public:
    explicit loginsession(QObject *parent = nullptr);
    ~loginsession();
    void user_login(QString email, QString password);
    void user_register(QString username, QString password);
    void establish_connect();
    void logout();
    void send_message(QString to_email, QString msg);
    void email_verify(int code);

signals:
    void connection_error();
    void login_return(int result);
    void register_return(int result);
    void general_return(int result);
    void sig_logout();
    void sig_receive_message(QString from_username, QString msg);

private:
    XMY_tcpsocket *socket;
    xmyUserSettings *settings;
    QString token;
    QString email;

private slots:
    void slot_connected();
    void slot_disconnected();
    void callback_process(QJsonObject data);
    void slot_connection_error();
};

#endif // LOGINSESSION_H
