#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QMainWindow>
#include<QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>
#include<QObject>

#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "xmyusersettings.h"
extern XMY_tcpsocket *tcp;
extern QString NAME;
extern QString friendname;
namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT


public:
    explicit chat(QWidget *parent = nullptr);
    chat(XMY_tcpsocket *socket){
        tcpSocket = socket;
    }
    void initTCP();
    void newConnect();
    void initInterface();
    void receiveMessage(QJsonObject data);
    void addedFriend(QJsonObject data);

    ~chat();

private slots:

    //  接收服务器发送的数据
    void receiveData(QJsonObject data);
    //  向服务器发送数据
    void sendData();
    void on_pushButton_send_clicked();
    //浏览文件
    void selectFile();
    //发送文件
    void sendFile();
    //更新文件发送进度
    void updateFileProgress(qint64);
    //更新文件接收进度
    void updateFileProgress();


    void on_pushButton_select_clicked();

private:
    Ui::chat *ui;
    XMY_tcpsocket *tcpSocket;

    ///文件传送
    QFile *localFile;
    ///文件大小
    qint64 totalBytes;      //文件总字节数
    qint64 bytesWritten;    //已发送的字节数
    qint64 bytestoWrite;    //尚未发送的字节数
    qint64 filenameSize;    //文件名字的字节数
    qint64 bytesReceived;   //接收的字节数
    ///每次发送数据大小
    qint64 perDataSize;
    QString filename;
    ///数据缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    //系统时间
    QDateTime current_date_time;
    QString str_date_time;
    QString datas;
    //接受到的数据


};

#endif // CHAT_H
