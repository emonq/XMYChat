#ifndef XMY_DATABASE_H
#define XMY_DATABASE_H

#define DB_FILE "xmychat.db"

#include "../XMYChatShare/xmy_basic.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class XMY_database : public QObject
{
    Q_OBJECT
public:
    explicit XMY_database(QObject *parent = nullptr);
    bool connect_db();
    void disconnect_db();
    bool init_db();
    int get_user_by_email(QString email, QMap<QString,QVariant>&info, QString fields);
    int new_user(QString email, QString password, QString username);
    bool set_user_by_email(QString email, QString fields, QVariant value);

signals:
    void new_log(QString msg);

private:
    QSqlDatabase db;

};

#endif // XMY_DATABASE_H
