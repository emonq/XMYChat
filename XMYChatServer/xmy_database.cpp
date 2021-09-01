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
        if(QSqlQuery("SELECT u_username,u_email,u_password,is_banned,is_waiting_verification,u_verification_code,u_friends FROM users").exec()) {
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
    query.prepare("CREATE TABLE users(u_email TEXT PRIMARY KEY, u_password TEXT NOT NULL, u_username TEXT, is_banned INT DEFAULT 0, is_waiting_verification INT NOT NULL DEFAULT 1, u_verification_code INT, u_friends TEXT)");
    if(!query.exec()) {
        emit new_log(query.lastError().text());
        return false;
    }
    else emit new_log("Database initialized.");
    return true;
}

int XMY_database::get_user_by_email(QString email, QMap<QString,QVariant>&info, QString fields)
{
    QStringList fieldList=fields.split(',');
    QSqlQuery query;
    query.prepare(QString("SELECT %1 FROM users WHERE u_email=:email").arg(fields));
    query.bindValue(":email",email);
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

int XMY_database::new_user(QString email, QString password, QString username)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users(u_email,u_password,u_username) VALUES(:email,:password,:username)");
    query.bindValue(":email",email);
    query.bindValue(":password",password);
    query.bindValue(":username",username);
    if(!query.exec()) {
        emit new_log(query.lastError().text());
        return false;
    }
    return true;
}

bool XMY_database::set_user_by_email(QString email, QString field, QVariant value)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE users SET %1=:value WHERE u_email=:email").arg(field));
    query.bindValue(":email",email);
    query.bindValue(":value",value);
    if(query.exec()) {
        return true;
    }
    else {
        emit new_log(query.lastError().text());
        return false;
    }
}
