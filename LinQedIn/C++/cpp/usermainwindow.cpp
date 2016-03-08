#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include "showprofile.h"
#include "showprofilefind.h"
#include "modifyprofile.h"
#include <QMessageBox>

UserMainWindow::UserMainWindow(LinQedInClient* lC, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMainWindow), client(lC)
{    
    ui->setupUi(this);
    QString clientName=QString::fromStdString(client->getLogin());
    ui->nameLabel->setText(clientName);
}

UserMainWindow::~UserMainWindow(){
    delete ui;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

void UserMainWindow::findPerson(){
    QString Person=ui->FindAPersonText->text();
    if(!Person.size()){
        QMessageBox err;
        err.setText("Campo dati vuoto");
        err.exec();}

    else{
        if(!(Person.toStdString()==client->getLogin())){
            vector<string> info=client->find(Person.toStdString());
            if(info.size()!=0){
               ShowProfileFind* spf=new ShowProfileFind(info);
               spf->show();}
            else{
                QMessageBox err;
                err.setText("Utente Non trovato");
                err.exec();}
        }
        else{
            QMessageBox err;
            err.setText("Utilizza l'apposito pulsante per visualizzare il tuo profilo");
            err.exec();}
        }
}

void UserMainWindow::addFriend(){
    QString qUser=ui->addFriendTextLine->text();
    Utente* user=client->findByUsername(qUser.toStdString());
    if(user){
        client->addInRete(user);
    }
    else{
        QMessageBox err;
        err.setText("Utente non trovato");
        err.exec();}
}

void UserMainWindow::removeFriend(){
    QString qUser=ui->rimuoviUnaPersonaLineEdit->text();
    client->removeFormRete(qUser.toStdString());
}

void UserMainWindow::searchInNet(){
    ui->resultTable->setRowCount(0); //pulisce la tabella
    ui->showMessage->setText("");
    vector<vector<Utente*>::iterator> vettoreIt=client->searchInNet();
    if(vettoreIt.size()!=0){
       int i=0;
       for(vector<vector<Utente*>::iterator>::iterator it=vettoreIt.begin(); it!=vettoreIt.end(); ++it){
          Utente* user=client->findByUsername((*(*it))->getLogin());
          ui->resultTable->setRowCount(i+1);
          QTableWidgetItem* newItem=new QTableWidgetItem(QString::fromStdString(user->getName()));
          ui->resultTable->setItem(i,0,newItem);
          newItem=new QTableWidgetItem(QString::fromStdString(user->getSurname()));
          ui->resultTable->setItem(i,1,newItem);
          newItem=new QTableWidgetItem(QString::fromStdString(user->getLogin()));
          ui->resultTable->setItem(i,2,newItem);
          i++;
    }}
    else
        ui->showMessage->setText("Nessun amico aggiunto");
}

void UserMainWindow::showAllUsers(){
    ui->resultTable->setRowCount(0); //pulisce la tabella
    ui->showMessage->setText("");
    vector<vector<Utente*>::iterator> vettoreIt=client->search("all", "all");
    if(vettoreIt.size()>1){ //Lui sarà iscritto quindi conta come utente1
       int i=0;
       for(vector<vector<Utente*>::iterator>::iterator it=vettoreIt.begin(); it!=vettoreIt.end(); ++it){
          Utente* user=client->findByUsername((*(*it))->getLogin());
          ui->resultTable->setRowCount(i+1);
          QTableWidgetItem* newItem=new QTableWidgetItem(QString::fromStdString(user->getName()));
          ui->resultTable->setItem(i,0,newItem);
          newItem=new QTableWidgetItem(QString::fromStdString(user->getSurname()));
          ui->resultTable->setItem(i,1,newItem);
          newItem=new QTableWidgetItem(QString::fromStdString(user->getLogin()));
          ui->resultTable->setItem(i,2,newItem);
          i++;
    }}
    else
        ui->showMessage->setText("Nessun altro utente iscritto oltre a te");
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

//VOID?
void UserMainWindow::on_findAPersonButton_clicked(){
    findPerson();
}

void UserMainWindow::on_ShowYourProfileButton_clicked(){
    ShowProfile* sp=new ShowProfile(client);
    sp->show();
}

void UserMainWindow::on_ModifyYourProfileButton_clicked(){
    ModifyProfile* mp=new ModifyProfile(client->getUtente());
    mp->show();
}

void UserMainWindow::on_addFriendButton_clicked(){
    addFriend();
}
void UserMainWindow::on_removeANetPersonButton_clicked(){
    removeFriend();
}

void UserMainWindow::on_showAllContact_clicked(){
    searchInNet();
}

void UserMainWindow::on_showAllUsers_clicked(){
    showAllUsers();
}

void UserMainWindow::on_closeButton_clicked(){
    client->saveDB();
    emit clClose();
    this->close();
    delete client;
}

