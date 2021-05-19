#ifndef USERCLIENT_H
#define USERCLIENT_H

#include <QDialog>

namespace Ui {
class UserClient;
}

class UserClient : public QDialog
{
    Q_OBJECT

public:
    explicit UserClient(QWidget *parent = nullptr);
    ~UserClient();

private slots:
    void on_pushButton_quitApplication_clicked();

    void on_pushButton_enterRaffle_clicked();

private:
    Ui::UserClient *ui;
};

#endif // USERCLIENT_H
