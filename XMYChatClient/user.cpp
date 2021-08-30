#include "user.h"
#include "ui_user.h"
#include"chat.h"
#include"addfriend.h"
#include"addfriend.h"
#include<QDataStream>
#include<QtNetwork>
#include<QFileDialog>
QString friendname;
User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{

    ui->setupUi(this);
    Init();
}

User::~User()
{
    delete ui;
}
void User::Init(){
    tcpsocket = tcp;
    ui->lineEdit_friendnum->setReadOnly(true);
    ui->lineEdit_userName->setReadOnly(true);
    //用户名、好友人数插入
    ui->lineEdit_userName->setText(tr("用户: %1").arg(NAME));
    ui->lineEdit_friendnum->setText(tr("好友人数: 0"));
    ui->label->setText(tr("欢迎您，%1").arg(NAME));
    connect(tcpsocket,SIGNAL(receive_json(data)),this,SLOT(receiveData(data)));
}
void User::receiveData(QJsonObject(data)){
    int type = data.value("type").toInt();
    QString name = data.value("name").toString();
    if(name == NAME) //确认是发给自己的
    {
        switch (type) {
        case TYPE_UPDATE_FRIEND: {
            updateFriend(data);
            break;
        }
        case TYPE_ADD_FRIEND : addFriend(data); break;
        case TYPE_UPDATE_HEAD : gethead(data.value("head").toString());
        case TYPE_DELETE : updateFriend(data);
        }
    }


}
void User::updateFriend(QJsonObject data){
    int num = data.value("num").toInt();
    ui->lineEdit_friendnum->setText(tr("好友人数: %1").arg(num));
    int n = ui->listWidget->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        delete item;
    }
    QJsonObject::Iterator it;
    int i = 0;
    for(it = data.begin();it != data.end();it++){
        QString name = data.value("name").toString(); //好友名字
        QString head = data.value("head").toString();  //好友头像
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(name);
        item->setIcon(QIcon(tr(":/images/%1.png").arg(head)));
        ui->listWidget->addItem(item);
        i++;
    }
}
//更新好友数，从服务端传回 好友总数、 每一个好友名字、好友头像

void User::addFriend(QJsonObject data){
    QString name = data.value("name").toString();
    QMessageBox::StandardButton rb = QMessageBox::information(NULL, tr("好友请求"),
                                 tr("%1想添加您为好友，是否同意请求？").arg(NAME),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        QJsonObject data_send;
        data_send.insert("type",TYPE_ADDED_FRIEND);
        data_send.insert("friendname",name);
        data_send.insert("username",NAME);
        tcpsocket->send_json(data_send);
    }
}



void User::gethead(const QString &head){
    //头像插入
   ui->label_headPortrait->setStyleSheet(tr("image: url(:/head/images/%1.png)").arg(head));
}

void User::on_pushButton_clicked()
{
    AddFriend *w;
    w = new AddFriend;
    w->show();
}
void User::on_listWidget_clicked(const QModelIndex &index)
{
    int count = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    friendname = ui->listWidget->item(count)->text();
   //获取内容
    chat *w;
    w = new chat;
    w->show();
}


void User::on_pushButton_delete_clicked()
{
    int count = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    friendname = ui->listWidget->item(count)->text();
    QMessageBox::StandardButton rb = QMessageBox::information(NULL, tr("删除好友"),
                                 tr("确定删除好友%1").arg(friendname),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        QJsonObject data_send;
        data_send.insert("type",TYPE_DELETE);
        data_send.insert("name",NAME);
        data_send.insert("friendname",friendname);
        tcpsocket->send_json(data_send);
        //服务端给 删的人和被删的人发送 TYPE＿delete

    }
}

