#include "clientdatabase.h"

ClientDatabase::ClientDatabase(QObject *parent, QString email) : QObject(parent)
{
    this->email=email;
    db=QSqlDatabase::addDatabase("QSQLITE");
    connect_db();
}

bool ClientDatabase::connect_db()
{
    db.setDatabaseName(email+".db");
    if(!db.open()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

void ClientDatabase::disconnect_db()
{
    db.close();
}

bool ClientDatabase::add_friend(QString email)
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE %1(id INT PRIMARY KEY, message TEXT, time TEXT, sender TEXT)").arg(email));
    if(!query.exec()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

bool ClientDatabase::delete_friend(QString email)
{
    QSqlQuery query;
    query.prepare(QString("DROP TABLE %1").arg(email));
    if(!query.exec()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

bool ClientDatabase::get_messages_by_email(QString email, QList<chatMessage> &messages)
{
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1 ORDER BY id").arg(email));
    if(!query.exec()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    messages.clear();
    while(query.next()) {
        messages.append(chatMessage(query.value("sender").toString(),query.value("time").toString(),query.value("message").toString()));
    }
    return true;
}


bool ClientDatabase::append_message(QString email, QString message, QString time)
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1(message,time) VALUES(:message,:time)").arg(email));
    query.bindValue(":message",message);
    query.bindValue(":time",time);
    if(!query.exec()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}
