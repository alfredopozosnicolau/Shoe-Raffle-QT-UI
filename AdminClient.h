#ifndef ADMINCLIENT_H
#define ADMINCLIENT_H

#include <QDialog>

namespace Ui {
class AdminClient;
}

class AdminClient : public QDialog
{
    Q_OBJECT

public:
    explicit AdminClient(QWidget *parent = nullptr);
    ~AdminClient();

private slots:
    void on_pushButton_QuitApplication_clicked();

    void on_pushButton_DeleteEntry_clicked();

    void on_pushButton_saveEntries_clicked();

    void on_pushButton_chooseWinner_clicked();

    void on_pushButtonExportWinners_clicked();

private:
    Ui::AdminClient *ui;
};

#endif // ADMINCLIENT_H
