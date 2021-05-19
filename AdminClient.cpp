#include "AdminClient.h"
#include "ui_AdminClient.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

//Reads entries from files and then displays them on admin ui
AdminClient::AdminClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminClient)
{
    ui->setupUi(this);

    // open raffle entrie files to read
    QFile raffleEntries("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/raffleEntries.txt");//change your file location here PROFESSER MILLER


    if(!raffleEntries.open(QFile::ReadOnly)){
        QMessageBox::warning(this, "ERROR", "file not open");
    }
    QTextStream in(&raffleEntries);

    //reads all the raffle entries and displays them on a list widget
    while(!raffleEntries.atEnd()){
        ui->listWidget_RaffleEntries->addItem(raffleEntries.readLine());
        }
    //display how many entries there are
    int size = ui->listWidget_RaffleEntries->count();
    ui->label_numOfEntries->setText(QString::number(size));
}

AdminClient::~AdminClient()
{
    delete ui;
}

// Quit Application button
void AdminClient::on_pushButton_QuitApplication_clicked()
{
    QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Quit Application", "Are you sure you want to quit the application?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
            QApplication::quit();
          } else {
          }

}

//Delete the selected raffle entry from list
void AdminClient::on_pushButton_DeleteEntry_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget_RaffleEntries->selectedItems();

    //Delete selected entry from list
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget_RaffleEntries->takeItem(ui->listWidget_RaffleEntries->row(item));
    }
    int size = ui->listWidget_RaffleEntries->count();
    ui->label_numOfEntries->setText(QString::number(size));
}

// Saves the entries on the list to the file
void AdminClient::on_pushButton_saveEntries_clicked()
{
    // Opens file to write to entries to
    QFile raffleEntries("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/raffleEntries.txt");//change your file location here PROFESSER MILLER
        if (raffleEntries.open(QIODevice::WriteOnly | QIODevice::Text)) {

            // writes entries to file
            QTextStream stream(&raffleEntries);
            for (int i = 0; i < ui->listWidget_RaffleEntries->count(); i++) {
                QListWidgetItem *item = ui->listWidget_RaffleEntries->item(i);
                stream << item->text();
            }

            raffleEntries.close();
           }

        //Update raffle entries amount
        int size = ui->listWidget_RaffleEntries->count();
        ui->label_numOfEntries->setText(QString::number(size));
}

// choose random singular winner
void AdminClient::on_pushButton_chooseWinner_clicked()
{
    // create array of string that stores all entries
    QString entries[ui->listWidget_RaffleEntries->count()];
    int size = ui->listWidget_RaffleEntries->count();
    int randomNumber = (rand() % size);

    //for loop to fill array with entries
    for (int i = 0; i < ui->listWidget_RaffleEntries->count(); i++) {
        QListWidgetItem *item = ui->listWidget_RaffleEntries->item(i);
        entries[i] = item->text();
    }
    //random number location for the size of the array
    ui->textBrowser_winnerDisplay->setText(entries[randomNumber]);
}

// export list of winners to file
void AdminClient::on_pushButtonExportWinners_clicked()
{
    //gets number of winners wanted, entries string array, size and hashset
    int amountOfWinners = ui->spinBoxAmountOfWinners->value();
    QString entries[ui->listWidget_RaffleEntries->count()];
    int size = ui->listWidget_RaffleEntries->count();
    QSet<int> hashSet;

    // fill array
    for (int i = 0; i < ui->listWidget_RaffleEntries->count(); i++) {
        QListWidgetItem *item = ui->listWidget_RaffleEntries->item(i);
        entries[i] = item->text();
    }

    //check for valid input from admin
    if(amountOfWinners == 0 || amountOfWinners > size){
        QMessageBox::warning(this, "ERROR", "Please check spinbox entry and make sure it is valid");
    }else{

    //create file to write winners to
    QFile raffleWinners("C:/Users/Skylake/Dropbox/My PC (Alfredos-PC)/Desktop/Adv C++/QT Projects/LoginScreen/RaffleWinners.txt");//change your file location here PROFESSER MILLER
        if (raffleWinners.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // bind it
            QTextStream stream(&raffleWinners);
            while(amountOfWinners > 0){
                int randomNumber = (rand() % size);
                if(!hashSet.contains(randomNumber)){ //checks to make sure no winners are repeated
                    hashSet.insert(randomNumber);
                    stream << entries[randomNumber];
                    amountOfWinners--;
                }

            }
            QMessageBox::information(this, "Task Successful", "The winners of the raffle have been picked and written to the txt file.");
            raffleWinners.close();
           }
    }
}
