#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include "loginsession.h"
#include "settingdialog.h"
#include "usermainwindow.h"
#include "verificationdialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
//    void register_finished(int result);
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_login_clicked();
    void on_actionServer_Settings_triggered();
    void slot_login_callback(int result);
//    void slot_register_callback(int result);
    void slot_general_callback(int result);
    void on_pushButton_register_clicked();

private:
    Ui::LoginWindow *ui;
    loginsession *session;
    xmyUserSettings *settings;
    bool check_form();
    void verify();
    void set_widgets(bool status);
};
#endif // LOGINWINDOW_H
