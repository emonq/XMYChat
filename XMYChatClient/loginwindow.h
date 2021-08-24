#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <cstring>

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
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
