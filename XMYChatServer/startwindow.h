#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#define DEBUG_MODE true

#include <QMainWindow>
#include <q_tcpserver.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void show_log(QString msg);

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_clicked();

    void on_actionRefresh_IP_triggered();

private:
    Ui::StartWindow *ui;
    Q_tcpserver *tcpserver;
    void fill_ip_addr();
};
#endif // STARTWINDOW_H
