#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "UserClient.h"
#include "AdminClient.h"

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
    void on_pushButton_Login_clicked();

    void on_pushButton_Register_clicked();

private:
    Ui::LoginWindow *ui;
    UserClient *userClient;
    AdminClient *adminClient;
};
#endif // LOGINWINDOW_H
