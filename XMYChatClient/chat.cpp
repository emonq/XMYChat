
#include "chat.h"
#include "ui_chat.h"
#include"addfriend.h"
#include<QDataStream>
#include<QtNetwork>
#include<QFileDialog>
#include<QKeyEvent>
chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    this->initTCP();
    this->initInterface();
}


chat::~chat()
{
    delete ui;
}

void chat::initInterface(){

    ui->textEdit_2->setReadOnly(true);
    ui->label_friendname->setText(friendname);

    //文件传送相关变量初始化
    ///每次发送数据大小为64kb
    perDataSize = 64*1024;
    totalBytes = 0;
    bytestoWrite = 0;
    bytesWritten = 0;
    bytesReceived = 0;
    filenameSize = 0;

//    connect(tcpSocket,&XMY_tcpsocket::receive_json,this,SLOT(receiveData()));
    connect(this->ui->pushButton_select,SIGNAL(clicked()),this,SLOT(selectFile()));
    connect(this->ui->pushButton_sendProfile,SIGNAL(clicked()),this,SLOT(sendFile()));

}

void chat::initTCP()
{
    tcpSocket = tcp;
    connect(tcpSocket,SIGNAL(receive_json(data)),this,SLOT(receiveData(data)));

}

void chat::receiveMessage(QJsonObject data){
    QString message = data.value("message").toString();
    QString name = data.value("name").toString();
    current_date_time = QDateTime::currentDateTime();
    str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    message = name + name  +str_date_time+"\n"+message;
    ui->textEdit_2->append(message);
}
//接收消息 需要服务端发来的 用户姓名，消息内容


void chat::receiveData(QJsonObject data)
{
    QString name = data.value("name").toString();
    if(name == NAME) //确认消息是发给自己的
    {
        switch (data.value("type").toInt()){
        case TYPE_RECEIVE_MESSAGE: receiveMessage(data); break;
        }
    }
}

void chat::sendData()
{
    //发送数据 发送给服务端 发送的消息、发送者和接收者
    QString str = ui->textEdit->toPlainText();
    if(str.trimmed() != tr("")){
        QJsonObject Message;
        Message.insert("type",TYPE_SEND_MESSAGE);
        Message.insert("message",str);
        QString userName = NAME;
        QString sendName = ui->label_friendname->text();
        qDebug() << userName;
        Message.insert("name",userName);
        Message.insert("sendname",sendName);
        tcpSocket->send_json(Message);
        current_date_time = QDateTime::currentDateTime();
        str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        str = NAME + " (YOU) "  +str_date_time+"\n"+str;
        ui->textEdit_2->append(str);
        ui->textEdit->clear();
    }


}

void chat::on_pushButton_send_clicked()
{
     sendData();
}

void chat::selectFile()
{

    //文件传送进度更新
    connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));
    this->filename = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    ui->lineEdit_filename->setText(filename);
}

void chat::sendFile()
{
    this->localFile = new QFile(filename);
    if(!localFile->open(QFile::ReadOnly))
    {

        return;
    }
    ///获取文件大小
    this->totalBytes = localFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_4_8);
    QString currentFileName = filename.right(filename.size()-filename.lastIndexOf('/')-1);

    qDebug()<<sizeof(currentFileName);
    //保留总代大小信息空间、文件名大小信息空间、文件名
    sendout<<qint64(0)<<qint64(0)<<currentFileName;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));

    bytestoWrite = totalBytes-tcpSocket->write(outBlock);
    outBlock.resize(0);
}

void chat::updateFileProgress(qint64 numBytes)
{
    //已经发送的数据大小
    bytesWritten += (int)numBytes;

    //如果已经发送了数据
    if(bytestoWrite > 0)
    {
        outBlock = localFile->read(qMin(bytestoWrite,perDataSize));
        ///发送完一次数据后还剩余数据的大小
        bytestoWrite -= ((int)tcpSocket->write(outBlock));
        ///清空发送缓冲区
        outBlock.resize(0);
    }
    else
        localFile->close();
    //如果发送完毕
    if(bytesWritten == totalBytes)
    {
        ui->lineEdit_filename->setText("文件发送成功!");
        localFile->close();
        //fileSocket->close();
    }
}
void chat::updateFileProgress()
{
    QDataStream inFile(this->tcpSocket);
    inFile.setVersion(QDataStream::Qt_4_8);

    ///如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((tcpSocket->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tcpSocket->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            filename = "ServerData/"+filename;
            localFile = new QFile(filename);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug()<<"Server::open file error!";
                return;
            }
        }
        else
            return;
    }
    //如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += tcpSocket->bytesAvailable();
        inBlock = tcpSocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    //数据接收完成时
    if(bytesReceived == totalBytes)
    {
        this->ui->textEdit->append("Receive file successfully!");
        bytesReceived = 0;
        totalBytes = 0;
        filenameSize = 0;
        localFile->close();
        //fileSocket->close();
        datas = inBlock;

    }
}
void chat::on_pushButton_select_clicked()
{
}

