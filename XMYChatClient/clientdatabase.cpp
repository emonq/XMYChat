#include "clientdatabase.h"

ClientDatabase::ClientDatabase(QObject *parent, QString email) : QObject(parent)
{
    this->email=email;
    db=QSqlDatabase::addDatabase("QSQLITE");
    connect_db();
}

bool ClientDatabase::connect_db()
{
    db.setDatabaseName(XMY_Utilities::emailtomd5(email)+".db");
    if(!db.open()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    qDebug()<<"connected database";
    return true;
}

void ClientDatabase::disconnect_db()
{
    db.close();
}

bool ClientDatabase::add_friend(QString email)
{
    qDebug()<<"Creating table "<<XMY_Utilities::emailtomd5(email);
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE %1(id INT PRIMARY KEY, message TEXT, time TEXT, sender TEXT)").arg("u_"+XMY_Utilities::emailtomd5(email)));
    if(!query.exec()) {
        qDebug()<<db.lastError().text();
        return false;
    }
    qDebug()<<email<<" table created";
    return true;
}

bool ClientDatabase::delete_friend(QString email)
{
    QSqlQuery query;
    query.prepare(QString("DROP TABLE %1").arg("u_"+XMY_Utilities::emailtomd5(email)));
    if(!query.exec()) {
        qDebug()<<db.lastError();
        return false;
    }
    return true;
}

bool ClientDatabase::get_messages_by_email(QString email, QList<chatMessage> &messages)
{
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1 ORDER BY id").arg("u_"+XMY_Utilities::emailtomd5(email)));
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

bool ClientDatabase::append_message(QString email, QString message, QString time, QString sender)
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1(message,time,sender) VALUES(:message,:time,:sender)").arg("u_"+XMY_Utilities::emailtomd5(email)));
    query.bindValue(":message",message);
    query.bindValue(":time",time);
    query.bindValue(":sender",sender);
    if(!query.exec()) {
        qDebug()<<db.lastError();
        return false;
    }
    return true;
}
