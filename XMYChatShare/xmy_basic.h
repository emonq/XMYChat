#ifndef XMY_BASIC_H
#define XMY_BASIC_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>
#include <QCryptographicHash>
#include <QUuid>

#define CONNECTION_CONNECTED 500
#define CONNECTION_ERROR 501
#define CONNECTION_TIMEOUT 502

#define SUCCESS 0
#define RECORD_NOT_FOUND 1
#define DB_ERROR 505

#define TYPE_LOGIN 0
#define TYPE_REGISTER 1
#define TYPE_SEND_MESSAGE 2
#define TYPE_RECEIVE_MESSAGE 3
#define TYPE_ADD_FRIEND 4

#define LOGIN_SUCCESS 0
#define LOGIN_INFO_ERROR 1
#define LOGIN_CONNECTION_ERROR 2
#define LOGIN_USER_NOT_FOUND 3
#define LOGIN_USER_BANNED 4

#define REGISTER_SUCCESS 0
#define REGISTER_USER_EXISTED 1
#define REGISTER_INFO_ERROR 2

#define REQUEST_ERROR 401


#endif // XMY_BASIC_H
