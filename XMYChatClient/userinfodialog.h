#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include <QDialog>
#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_utilities.h"

namespace Ui {
class UserInfoDialog;
}

class UserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    QHash<QString,QString> data;

    explicit UserInfoDialog(QWidget *parent = nullptr, QString username=QString(), QString email=QString());
    ~UserInfoDialog();

private slots:
    void on_pushButton_select_avatar_clicked();

    void on_lineEdit_username_textEdited(const QString &arg1);

    void on_lineEdit_email_textEdited(const QString &arg1);

    void on_lineEdit_password_textEdited(const QString &arg1);

private:
    Ui::UserInfoDialog *ui;
};

#endif // USERINFODIALOG_H
