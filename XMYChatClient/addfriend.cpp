
#include "addfriend.h"
#include "ui_addfriend.h"
AddFriend::AddFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    Init();
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::Init(){
    tcpsocket = tcp;
    connect(tcpsocket,SIGNAL(receive_json(data)),this,SLOT(receiveDatas(data)));
    //qDebug() << ui->label_head->styleSheet();
}
void AddFriend::receiveDatas(QJsonObject(data)){
    switch (data.value("type").toInt()){
    case FIND: addinformation(data); break;
    case NOFIND: ui->label->setText(tr("没有找到该用户，请检查用户名是否正确"));
    case HAVEADDED: ui->label->setText(tr("该用户已经是您的好友，请勿重复添加"));
    }
}
void AddFriend::addinformation(QJsonObject data){
    QString name = data.value("name").toString();
    QString head = data.value("head").toString();
    //image: url(:/head/images/A.jpg)
    head = tr("image: url(:/head/images/") + head + tr(".png)");
    ui->label_head->setStyleSheet(head);
    ui->label->setText(name);
}

void AddFriend::on_pushButton_find_clicked()//查找
{
    QString username = ui->lineEdit->text();
    QJsonObject addFriend;
    addFriend.insert("type",TYPE_FIND_FRIEND);
    addFriend.insert("name",NAME); //选择加好友的那个人
    addFriend.insert("addname",username); //被加的那个人
    tcpsocket->send_json(addFriend);
}


void AddFriend::on_pushButton_add_clicked()//添加
{
    QJsonObject addFriend;
    QString username = ui->lineEdit->text();
    addFriend.insert("type",TYPE_ADD_FRIEND);
    addFriend.insert("name",NAME); //选择加好友的那个人
    addFriend.insert("addname",username); //被加的那个人
    tcpsocket->send_json(addFriend);
}

