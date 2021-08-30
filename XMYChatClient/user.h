#ifndef USER_H
#define USER_H

#include <QDialog>
#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "xmyusersettings.h"
extern XMY_tcpsocket *tcp;
extern QString NAME;
namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    XMY_tcpsocket *tcpsocket;
    void updateFriend(QJsonObject data); //从数据库中获得当前好友
    void Init();
    void gethead(const QString &head);
    void addFriend(QJsonObject data);
    ~User();

private slots:
    void on_pushButton_clicked();
    void receiveData(QJsonObject data);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_delete_clicked();

private:
    Ui::User *ui;
};

#endif // USER_H
