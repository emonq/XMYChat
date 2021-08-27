#ifndef XMY_DATABASE_H
#define XMY_DATABASE_H

#define DB_FILE "test.db"

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
    int get_user_by_username(QString username, QMap<QString,QVariant>&info, QString fields);
    int new_user(QString username, QString password);

signals:
    void new_log(QString msg);

private:
    QSqlDatabase db;

};

#endif // XMY_DATABASE_H
