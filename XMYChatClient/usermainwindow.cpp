#include "usermainwindow.h"
#include "ui_usermainwindow.h"

UserMainWindow::UserMainWindow(QWidget *parent, loginsession* session) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow),
    session(session)
{
    if(!QFile(".cache\\default.png").exists()) {
        QString default_avatar="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";
        XMY_Utilities::checkDir(".cache");
        XMY_Utilities::save_pic_from_base64(default_avatar,".cache\\default.png");
    }
    ui->setupUi(this);
    connect(session,&loginsession::sig_logout,this,&UserMainWindow::slot_logout);
    connect(session,&loginsession::sig_receive_message,this,&UserMainWindow::slot_receive_message);
    ui->label_avatar->setScaledContents(true);
    ui->label_avatar_friend->setScaledContents(true);
    connect(session,&loginsession::info_refreshed,this,&UserMainWindow::slot_info_refresh);
    connect(session,&loginsession::avatar_got,this,&UserMainWindow::slot_avatar_got);
    connect(session,&loginsession::friend_list_refreshed,this,&UserMainWindow::slot_friend_list_refreshed);
    connect(session,&loginsession::user_found,this,&UserMainWindow::slot_user_found);
    connect(session,&loginsession::user_not_found,this,[=](){
        QMessageBox warning(QMessageBox::Warning,"Error","User not found",QMessageBox::Ok,this);
        warning.exec();
    });
    connect(session,&loginsession::send_message_failed,this,[=](){
        QMessageBox warning(QMessageBox::Warning,"Message send error","Your message is failed to send. It may because your friend is offline currently.",QMessageBox::Ok,this);
        warning.exec();
    });
    connect(ui->lineEdit_usersearchinput,&QLineEdit::returnPressed,this,[=](){
        ui->pushButton_search->click();
    });
    session->get_user_info();
    ui->pushButton_send->setEnabled(false);
    XMY_Utilities::checkDir(".cache");
    session->fetch_friend_list();
    session->get_avatar();
    ui->plainTextEdit_msginput->installEventFilter(this);
}

UserMainWindow::~UserMainWindow()
{
    session->logout();
    session->deleteLater();
    delete ui;
}

void UserMainWindow::slot_logout()
{
    QMessageBox msgbox(QMessageBox::Warning,"Logged out","You have logged out");
    msgbox.exec();
    close();
}

void UserMainWindow::slot_receive_message(chatMessage msg)
{
    if(msg.sender==ui->label_email_friend->text()){
        show_messages();
    }
    else {
        session->friend_item.value(msg.sender)->setBackground(QColor("pink"));
    }
}

void UserMainWindow::on_pushButton_send_clicked()
{
    QString to_email=ui->label_email_friend->text().trimmed().toLower();
    QString msg=ui->plainTextEdit_msginput->toPlainText();
    session->send_message(to_email,msg);
    ui->plainTextEdit_msginput->clear();
    ui->listWidget_messages->addItem(XMY_Utilities::get_time_string()+" - "+session->info.value("email"));
    ui->listWidget_messages->addItem(msg);
    ui->listWidget_messages->scrollToBottom();
}

void UserMainWindow::slot_info_refresh()
{
    fill_user_info();
//    session->get_avatar();
}

void UserMainWindow::slot_friend_list_refreshed()
{
    session->friend_item.clear();
    ui->listWidget_friends->clear();
    for(auto &i:session->friends) {
        QListWidgetItem *item=new QListWidgetItem(ui->listWidget_friends);
        item->setBackground(QColor("white"));
        item->setIcon(QIcon(XMY_Utilities::get_avatar_filename(".cache\\",i.email)));
        item->setText(i.username+'\n'+i.email);
        session->friend_item[i.email]=item;
        ui->listWidget_friends->addItem(item);
    }
    if(!session->friend_email_list.contains(ui->label_email_friend->text())) clear_friend_info();
    ui->label_friends->setText(QString("%1 friends:").arg(session->friend_item.count()));
}

void UserMainWindow::slot_avatar_got(QString email)
{
    QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
    QPixmap pic(filename);
    if(email==session->info.value("email")) {
        ui->label_avatar->setPixmap(pic);
    }
    else {
        if(session->friend_item.contains(email)) session->friend_item[email]->setIcon(pic);
    }
}

void UserMainWindow::slot_user_found(userStruct user)
{
    FriendSearchDialog dialog(session,this,user.username,user.email);
    if(dialog.exec()==QDialog::Accepted) {
        if(!session->friend_email_list.contains(user.email)){
            session->add_user(user.email);
            QListWidgetItem* item=new QListWidgetItem(ui->listWidget_friends);
            item->setIcon(QPixmap(XMY_Utilities::get_avatar_filename(".cache\\",user.email)));
            item->setText(user.username+'\n'+user.email);
            session->friend_email_list.append(user.email);
            session->friends.append(user);
            session->friend_item.insert(user.email,item);
            slot_friend_list_refreshed();
        }
        else {
            QMessageBox warning(QMessageBox::Warning,"Error","This user has been your friend",QMessageBox::Ok,this);
            warning.exec();
        }
    }
}

void UserMainWindow::on_pushButton_logout_clicked()
{
    session->logout();
}

void UserMainWindow::on_pushButton_editinfo_clicked()
{
    qDebug()<<session->info;
    UserInfoDialog* infodialog=new UserInfoDialog(this,session->info["username"],session->info["email"]);
    if(infodialog->exec()==QDialog::Accepted) {
        QJsonObject data;
        data.insert("type",TYPE_INFO_MODIFY);
        data.insert("email",session->info["email"]);
        if(infodialog->data.contains("avatar")) XMY_Utilities::save_pic_from_base64(infodialog->data.value("avatar"),XMY_Utilities::get_avatar_filename(".cache\\",session->info["email"]));
        for(QHash<QString, QString>::iterator i=infodialog->data.begin();i!=infodialog->data.end();i++) {
            data[i.key()]=i.value();
            session->info[i.key()]=i.value();
        }
        session->user_info_modify(data);
        qDebug()<<data;
        fill_user_info();
    }
    infodialog->deleteLater();
}

void UserMainWindow::fill_user_info()
{
    QPixmap avatar(".cache\\"+XMY_Utilities::emailtomd5(session->info["email"])+".png");
    avatar.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setPixmap(avatar);
    ui->label_email->setText(session->info["email"]);
    ui->label_username->setText(session->info["username"]);
    setWindowTitle(session->info["email"]);
}

void UserMainWindow::clear_friend_info()
{
    ui->label_avatar_friend->clear();
    ui->label_email_friend->clear();
    ui->label_username_friend->clear();
    ui->listWidget_messages->clear();
}

void UserMainWindow::on_listWidget_friends_itemClicked(QListWidgetItem *item)
{
    item->setBackground(QColor("white"));
    QStringList info=item->text().split('\n');
    ui->label_email_friend->setText(info[1]);
    ui->label_username_friend->setText(info[0]);
    QPixmap avatar(XMY_Utilities::get_avatar_filename(".cache\\",info[1]));
    ui->label_avatar_friend->setPixmap(avatar);
    ui->pushButton_send->setEnabled(true);
    show_messages();
}


void UserMainWindow::on_pushButton_search_clicked()
{
    if(ui->lineEdit_usersearchinput->text().isEmpty() || !XMY_Utilities::check_valid_email(ui->lineEdit_usersearchinput->text())) {
        QMessageBox warning(QMessageBox::Warning,"Error","Please input a valid email",QMessageBox::Ok,this);
        warning.exec();
    }
    else {
        if(ui->lineEdit_usersearchinput->text()==session->info.value("email")) {
            QMessageBox warning(QMessageBox::Warning,"Error","You can't add yourself to contact!",QMessageBox::Ok,this);
            warning.exec();
        }
        else session->search_user(ui->lineEdit_usersearchinput->text());
    }
    ui->lineEdit_usersearchinput->clear();
}

void UserMainWindow::show_messages()
{
    QString email=ui->label_email_friend->text();
    if(email.isEmpty()) return;
    QList<chatMessage> msg;
    msg=session->get_messages_by_email(email);
    ui->listWidget_messages->clear();
    for(auto &i:msg) {
        ui->listWidget_messages->addItem(i.time+" - "+i.sender);
        ui->listWidget_messages->addItem(i.msg);
    }
    ui->listWidget_messages->scrollToBottom();
}

bool UserMainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object==ui->plainTextEdit_msginput) {
        if(event->type()==QEvent::KeyPress) {
            QKeyEvent* peve=dynamic_cast<QKeyEvent*>(event);
            if((peve->modifiers() & Qt::ControlModifier) && (peve->key()==Qt::Key_Return || peve->key()==Qt::Key_Enter)) {
                ui->plainTextEdit_msginput->insertPlainText("\n");
                return true;
            }
            if(peve->key()==Qt::Key_Return || peve->key()==Qt::Key_Enter) {
                if(ui->pushButton_send->isEnabled()) on_pushButton_send_clicked();
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(object,event);
}


void UserMainWindow::on_listWidget_friends_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *curItem = ui->listWidget_friends->itemAt(pos);
        if (curItem == NULL)
            return;

        QMenu *popMenu = new QMenu(this);
        QAction *deleteSeed = new QAction(tr("Delete"), this);
        popMenu->addAction(deleteSeed);
        connect(deleteSeed, SIGNAL(triggered()), this, SLOT(deleteSeedSlot()));
        popMenu->exec(QCursor::pos());
        delete popMenu;
        delete deleteSeed;
}
void UserMainWindow::deleteSeedSlot()
{
    QListWidgetItem *item = ui->listWidget_friends->currentItem();
    if (item == NULL)
        return;
    QString email = item->text(); //好友邮箱
    email = email.split('\n')[1];
    int ch = QMessageBox::warning(NULL, "Warning",
                                  tr("Are you sure to delete %1?").arg(email),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if (ch != QMessageBox::Yes)
        return;
    if(ui->label_email_friend->text()==email) {
        clear_friend_info();
    }
    session->delete_user(email);
    int curIndex = ui->listWidget_friends->row(item);
    ui->listWidget_friends->takeItem(curIndex);
    delete item;
}
