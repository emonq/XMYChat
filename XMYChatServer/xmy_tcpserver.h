#ifndef XMY_TCPSERVER_H
#define XMY_TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostInfo>
#include <QTcpSocket>
#include <QCryptographicHash>

#include "xmy_database.h"
#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "../XMYChatShare/xmy_utilities.h"

class XMY_tcpserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit XMY_tcpserver(QObject *parent=Q_NULLPTR);
    QList<QHostAddress> get_addr();
    bool start_server(QHostAddress ip, int port);
    void stop_server();
    ~XMY_tcpserver();
    virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void receive_message(QString msg_from, QString msg);
    void new_log(QString msg);

private:
    XMY_database* db;
    QHash<QUuid,XMY_tcpsocket*> clients;
    QHash<QString, QUuid> loginusers;

    void user_authentication(QJsonObject login_info, QJsonObject& ret_data, QUuid socketId);
    void user_create(QJsonObject user_info, QJsonObject& ret_data);
    bool send_message(QString from_username, QString to_username, QString msg);
    bool email_verify(QString email, int code, QJsonObject& ret_data);
    void send_verification_code(QString email);
    bool fetch_friend_list(QString email, QJsonObject& ret);
    bool update_friend_list(QString email, QString f_email, friendOperations operation);
    void search_user(QString email, QJsonObject& ret);
    void add_friend(QString email1, QString email2);
    void delete_friend(QString email1, QString email2);
    void update_friend_list(QString email);
    void push_update_to_friends(QString email);

private slots:
    void slot_disconnected();
    void request_process(QJsonObject req);
    void handleEndOfRequest(QNetworkReply*);
};

#endif // XMY_TCPSERVER_H
