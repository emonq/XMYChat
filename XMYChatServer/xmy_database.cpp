#include "xmy_database.h"

XMY_database::XMY_database(QObject *parent) : QObject(parent)
{
    db=QSqlDatabase::addDatabase("QSQLITE");
}

bool XMY_database::connect_db()
{
    emit new_log("Connecting database");
    db.setDatabaseName(DB_FILE);
    if (db.open()) {
        if(QSqlQuery("SELECT u_username,u_email,u_password,is_banned FROM users").exec()) {
            emit new_log("Database connected.");
            return true;
        }
        else {
            emit new_log("Database not initialized.");
            return false;
        }
        return false;
    }
    else {
        emit new_log("Database connect failed!");
        return false;
    }
}

void XMY_database::disconnect_db()
{
    db.close();
}

bool XMY_database::init_db()
{
    QSqlQuery query;
    query.exec("DROP TABLE users");
    query.prepare("CREATE TABLE users(u_username TEXT PRIMARY KEY, u_password TEXT NOT NULL, u_email TEXT, is_banned INT)");
    if(!query.exec()) {
        emit new_log(query.lastError().text());
        return false;
    }
    else emit new_log("Database initialized.");
    return true;
}

int XMY_database::get_user_by_username(QString username, QMap<QString,QVariant>&info, QString fields)
{
    QStringList fieldList=fields.split(',');
    QSqlQuery query;
    query.prepare(QString("SELECT %1 FROM users WHERE u_username='%2'").arg(fields,username));
    if (!query.exec()) {
        emit new_log(query.lastError().text());
        return DB_ERROR;
    }
    if(!query.next()) return RECORD_NOT_FOUND;
    info.clear();
    for(auto& i:fieldList){
        info.insert(i,query.value(i));
    }
    return SUCCESS;
}

int XMY_database::new_user(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users(u_username,u_password) VALUES(:username,:password)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    if(!query.exec()) {
        emit new_log(query.lastError().text());
        return false;
    }
    return true;
}
