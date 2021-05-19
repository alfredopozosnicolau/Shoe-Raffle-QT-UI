#include "UserClient.h"
#include "ui_UserClient.h"
#include <QDialog>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

UserClient::UserClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserClient)
{
    ui->setupUi(this);
}

UserClient::~UserClient()
{
    delete ui;
}

//quit application file
void UserClient::on_pushButton_quitApplication_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit Application", "Are you sure you want to quit the application?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        QApplication::quit();
      } else {
      }
}

//submits raffle entries
void UserClient::on_pushButton_enterRaffle_clicked()
{
    //gets info from lines and stores them in a universal format
    QString email = ui->lineEdit_email->text();
    QString fullName = ui->lineEdit_fullName->text();
    QString phoneNumber = ui->lineEdit_phoneNumber->text();
    QString shoeSize = ui->lineEdit_shoeSize->text();

    QString entry = email + ":" + fullName + ":" + phoneNumber + ":" + shoeSize + "\n";

    //open raffle entry file to write information to
    QFile raffleEntries("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/raffleEntries.txt");//change your file location here PROFESSER MILLER

    // appenend open file and write entry to file
    if(raffleEntries.open(QFile::WriteOnly | QIODevice::Append)){
        QTextStream out(&raffleEntries);
        out << entry;
        raffleEntries.flush();
        raffleEntries.close();
    }
    else{
        QMessageBox::warning(this, "ERROR", "file not open");
    }

    //show success message to ensure the user their entry got submitted and then close application
    QMessageBox::information(this, "Raffle Entry Submitted!", "Your entry was successfully submitted, the application will now close to prevent duplicate submissions.");
    QApplication::quit();

}
