#ifndef CLIENTDATABASE_H
#define CLIENTDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

#include "../XMYChatShare/xmy_basic.h"

class ClientDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ClientDatabase(QObject *parent = nullptr, QString email="default");

private:
    QString email;
    QSqlDatabase db;

    bool connect_db();
    void disconnect_db();
    bool add_friend(QString email);
    bool delete_friend(QString email);
    bool get_messages_by_email(QString email, QList<chatMessage>& messages);
    bool append_message(QString email, QString message, QString time);

signals:


};

#endif // CLIENTDATABASE_H
