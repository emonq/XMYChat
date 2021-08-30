#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>
#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "xmyusersettings.h"
extern XMY_tcpsocket *tcp;
extern QString NAME;
namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    void Init();
    void addinformation(QJsonObject data); //表示查找后有这个人
    ~AddFriend();

private slots:
    void on_pushButton_find_clicked();
    void receiveDatas(QJsonObject data);

    void on_pushButton_add_clicked();

private:
    Ui::AddFriend *ui;
    XMY_tcpsocket *tcpsocket;
};

#endif // ADDFRIEND_H
