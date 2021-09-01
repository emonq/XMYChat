#ifndef LOGINSESSION_H
#define LOGINSESSION_H

#include <QObject>
#include <QTcpSocket>

#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "../XMYChatShare/xmy_utilities.h"
#include "xmyusersettings.h"
#include "clientdatabase.h"

class loginsession : public QObject
{
    Q_OBJECT
public:
    QHash<QString, QString> info;
    QList<userStruct> friends;
    QHash<QString, QListWidgetItem*> friend_item;
    QStringList friend_email_list;

    explicit loginsession(QObject *parent = nullptr);
    ~loginsession();
    void user_login(QString email, QString password);
    bool user_register(QString email, QString password, QString username);
    void establish_connect();
    void logout();
    void send_message(QString to_email, QString msg);
    void email_verify(int code);
    void user_info_modify(QJsonObject data);
    void get_user_info(QString email=QString());
    void fetch_friend_list();
    void get_avatar(QString email=QString(), QString md5=QString());
    void search_user(QString email);
    void add_user(QString email);
    void delete_user(QString email);
    QList<chatMessage> get_messages_by_email(QString email);

signals:
    void connection_error();
    void login_return(int result);
    void register_return(int result);
    void general_return(int result);
    void sig_logout();
    void sig_receive_message(chatMessage msg);
    void info_refreshed();
    void friend_list_refreshed();
    void avatar_got(QString email);
    void user_found(userStruct user);
    void user_not_found();
    void send_message_failed();

private:
    ClientDatabase *db;
    XMY_tcpsocket *socket;
    xmyUserSettings *settings;

private slots:
    void slot_connected();
    void slot_disconnected();
    void callback_process(QJsonObject data);
    void slot_connection_error();
};

#endif // LOGINSESSION_H
