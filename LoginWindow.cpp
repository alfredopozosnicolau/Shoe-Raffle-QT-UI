#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

//check login to see if valid
void LoginWindow::on_pushButton_Login_clicked()
{
    //store line edit fields to variables
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString login= username + ":" + password + "\n"; //create login format
    bool loginValid = false;

    //open login file to read logins
    QFile loginLogs("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/logins.dat");//change your file location here PROFESSER MILLER

    if(!loginLogs.open(QFile::ReadOnly)){
        QMessageBox::warning(this, "ERROR", "file not open");
    }
    QTextStream in(&loginLogs);

    //check binary file to see if login exists
    while(!loginLogs.atEnd()){
        if(login == loginLogs.readLine()){
            userClient = new UserClient(this);
            loginValid = true;
                    userClient->show();
        }
        //admin login here could be replaced with another binary file if want multiple admin logins
        else if(login == "admin:admin\n"){
            adminClient = new AdminClient(this);
             loginValid = true;
                    adminClient->show();
                    break;
        }
    }
    if(loginValid == false)
    QMessageBox::warning(this, "Login Not Valid", "Username and password not registered in system");

    loginLogs.close();
}

//register users login to file
void LoginWindow::on_pushButton_Register_clicked()
{
    //store username and password to varibles and then into login format
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString login= username + ":" + password + "\n";

    //open to write to binary file for logins
    QFile loginLogs("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/logins.dat");//change your file location here PROFESSER MILLER

    //appends to the current file and then writes login to file
    if(loginLogs.open(QFile::WriteOnly | QIODevice::Append)){
        QTextStream out(&loginLogs);
        out << login;
        loginLogs.flush();
        loginLogs.close();
        QMessageBox::information(this, "Registered Successfully", "Your username and password have been registered succesfully");
    }
    else{
        QMessageBox::warning(this, "ERROR", "file not open");
    }

}
