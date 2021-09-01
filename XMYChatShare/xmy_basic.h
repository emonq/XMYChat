#ifndef XMY_BASIC_H
#define XMY_BASIC_H

#define MAILGUN_KEY "Basic YXBpOmRhMzU0ZWY3ZjIxYTUyZTlkN2MzNmQ1NzZkNzE5MWVlLWZiODdhZjM1LTA2NDlmYmFm"

#include <utility>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include <QCryptographicHash>
#include <QUuid>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QEventLoop>
#include <QListWidgetItem>
#include <QMetaType>

#define CONNECTION_CONNECTED 500
#define CONNECTION_ERROR 501
#define CONNECTION_TIMEOUT 502

#define SUCCESS 0
#define RECORD_NOT_FOUND 1
#define DB_ERROR 505


#define TYPE_REGISTER 1
#define TYPE_SEND_MESSAGE 2
#define TYPE_RECEIVE_MESSAGE 3
#define TYPE_ADD_FRIEND 4
#define TYPE_LOGOUT 5
#define TYPE_FETCH_FRIEND_LIST 6
#define TYPE_VERIFY 7
#define TYPE_INFO_MODIFY 8
#define TYPE_LOGIN 9
#define TYPE_GET_USER_INFO 10
#define TYPE_GET_AVATAR 11
#define TYPE_SEARCH_USER 12
#define TYPE_DELETE_FRIEND 13

#define LOGIN_SUCCESS 0
#define LOGIN_INFO_ERROR 1
#define LOGIN_CONNECTION_ERROR 2
#define LOGIN_USER_NOT_FOUND 3
#define LOGIN_USER_BANNED 4
#define LOGIN_USER_WAITING_VERIFICATION 5

#define REGISTER_SUCCESS 0
#define REGISTER_USER_EXISTED 1
#define REGISTER_INFO_ERROR 2
#define REGISTER_WAITING_VERIFICATION 3
#define REGISTER_VERIFY_ERROR 4

#define GET_AVATAR_OK 0
#define GET_AVATAR_NOCHANGE 1

#define REQUEST_ERROR 400
#define INVALID_TOKEN 401

struct chatMessage {
    QString sender;
    QString time;
    QString msg;

    chatMessage(QString m_sender=QString(), QString m_time=QString(), QString m_msg=QString()) {
        sender=m_sender;
        time=m_time;
        msg=m_msg;
    }
};

struct userStruct {
    QString username;
    QString email;
    QString avatarmd5;

    userStruct(QString u_username=QString(), QString u_email=QString(), QString u_avatarmd5=QString()) {
        username=u_username;
        email=u_email;
        avatarmd5=u_avatarmd5;
    }
};

enum friendOperations {Add, Delete};

#endif // XMY_BASIC_H
