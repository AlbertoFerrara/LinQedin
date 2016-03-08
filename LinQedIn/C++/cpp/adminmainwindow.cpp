#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "registrationwindow.h"
#include "utentebasic.h"
#include "utentebusiness.h"
#include "utenteexecutive.h"
#include <QMessageBox>


AdminMainWindow::AdminMainWindow(LinQedInAdmin* ad, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMainWindow), admin(ad)
{
    ui->setupUi(this);
    connect(this, SIGNAL(userFound(QString)), this, SLOT(updateText(QString)));
    connect(this, SIGNAL(userNotFound(QString)), this, SLOT(updateText(QString)));

}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
    delete admin;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

void AdminMainWindow::clearTextBox(){
    ui->updateTextBrowser->setText("");
}

void AdminMainWindow::clearTable(){
    ui->resultTable->setRowCount(0);
}

void AdminMainWindow::printInfo(QString s){
    ui->updateTextBrowser->setText(s);
}


void AdminMainWindow::updateText(QString str){
    ui->updateTextBrowser->setText(str);
}

void AdminMainWindow::findUser(){
    clearTextBox();
    clearTable();
    if(ui->nameRadioButton->isChecked()){
        QString sname=ui->nameFindLineEdit->text();
        QString ssurname=ui->surnameFindLineEdit->text(); 
        vettoreIt=admin->search(sname.toStdString(), ssurname.toStdString());
        if(vettoreIt.size()==0){
            QMessageBox msg;
            msg.setText("Nessun Utente Trovato");
            msg.exec();}
        else{
        emit userFound("Trovato uno o più utenti");
        int i=0;
        for(vector<vector<Utente*>::iterator>::iterator it=vettoreIt.begin(); it!=vettoreIt.end(); ++it){
            Utente* user=admin->findByUsername((*(*it))->getLogin());
            ui->resultTable->setRowCount(i+1);
            QTableWidgetItem* newItem=new QTableWidgetItem(QString::fromStdString(user->getName()));
            ui->resultTable->setItem(i,0,newItem);
            newItem=new QTableWidgetItem(QString::fromStdString(user->getSurname()));
            ui->resultTable->setItem(i,1,newItem);
            newItem=new QTableWidgetItem(QString::fromStdString(user->getLogin()));
            ui->resultTable->setItem(i,2,newItem);
            string strtu;
            const UtenteBasic* uba = dynamic_cast<const UtenteBasic*>(user);
            if(uba){
                strtu="Basic";
            }
            else{
                const UtenteBusiness* ubu = dynamic_cast<const UtenteBusiness*>(user);
                if(ubu){
                    strtu="Business";
                }
                else{
                    const UtenteExecutive* uex = dynamic_cast<const UtenteExecutive*>(user);
                    if(uex){
                        strtu="Executive";
                    }}
            }
            newItem=new QTableWidgetItem(QString::fromStdString(strtu));
            ui->resultTable->setItem(i,3,newItem);
            i++;

        }

    }}
    else{
        if(ui->usernameRadioButton->isChecked()){
            QString susername=ui->usernameFindLineEdit->text();
            Utente* toFind=admin->findByUsername(susername.toStdString());
            if(toFind!=0){
                QString str=QString::fromStdString("Trovato Utente:\n")+susername;
                emit userFound(str);
                ui->resultTable->setRowCount(1);

                QString sname=QString::fromStdString(toFind->getName());
                QString ssurname=QString::fromStdString(toFind->getSurname());
                QTableWidgetItem* newItem=new QTableWidgetItem(sname);
                ui->resultTable->setItem(0,0,newItem);
                newItem=new QTableWidgetItem(ssurname);
                ui->resultTable->setItem(0,1,newItem);
                newItem=new QTableWidgetItem(susername);
                ui->resultTable->setItem(0,2,newItem);
                string strtu;
                const UtenteBasic* uba = dynamic_cast<const UtenteBasic*>(toFind);
                if(uba){
                    strtu="Basic";
                }
                else{
                    const UtenteBusiness* ubu = dynamic_cast<const UtenteBusiness*>(toFind);
                    if(ubu){
                        strtu="Business";
                    }
                    else{
                        const UtenteExecutive* uex = dynamic_cast<const UtenteExecutive*>(toFind);
                        if(uex){
                            strtu="Executive";
                        }}
                }
                newItem=new QTableWidgetItem(QString::fromStdString(strtu));
                ui->resultTable->setItem(0,3,newItem);

             }
            else{
                emit userNotFound(QString::fromStdString("Nessun Utente Trovato"));
                QMessageBox msg;
                msg.setText("Nessun Utente Trovato");
                msg.exec();}
        }
    }

}

void AdminMainWindow::deleteUser(){
            QString susername=ui->usernameDeleteLineEdit->text();
            Utente* toDelete=admin->findByUsername(susername.toStdString());
            if(toDelete!=0){
                admin->remove(toDelete);
                QString str=QString::fromStdString("Utente Eliminato:\n")+susername;
             clearTable();
             emit userFound(str);
             QMessageBox msg;
             msg.setText("Utente Eliminato");
             msg.exec();
             }
            else
                emit userNotFound(QString::fromStdString("Nessun Utente Trovato"));
        }


void AdminMainWindow::getAllUsers(){
    ui->resultTable->setRowCount(0); //pulisce la tabella
    vettoreIt=admin->search("all", "all");
    int i=0;
    for(vector<vector<Utente*>::iterator>::iterator it=vettoreIt.begin(); it!=vettoreIt.end(); ++it){
        Utente* user=admin->findByUsername((*(*it))->getLogin());
        ui->resultTable->setRowCount(i+1);
        QTableWidgetItem* newItem=new QTableWidgetItem(QString::fromStdString(user->getName()));
        ui->resultTable->setItem(i,0,newItem);
        newItem=new QTableWidgetItem(QString::fromStdString(user->getSurname()));
        ui->resultTable->setItem(i,1,newItem);
        newItem=new QTableWidgetItem(QString::fromStdString(user->getLogin()));
        ui->resultTable->setItem(i,2,newItem);
        string strtu;
        const UtenteBasic* uba = dynamic_cast<const UtenteBasic*>(user);
        if(uba){
            strtu="Basic";
        }
        else{
            const UtenteBusiness* ubu = dynamic_cast<const UtenteBusiness*>(user);
            if(ubu){
                strtu="Business";
            }
            else{
                const UtenteExecutive* uex = dynamic_cast<const UtenteExecutive*>(user);
                if(uex){
                    strtu="Executive";
                }}
        }
        newItem=new QTableWidgetItem(QString::fromStdString(strtu));
        ui->resultTable->setItem(i,3,newItem);
        i++;

    }
}

void AdminMainWindow::changeAccountType(){
    clearTextBox();
    QString susername=ui->usernameChangeLineEdit->text();
    QString str=QString::fromStdString("Utente Cambiato:\n");
    Utente* toChange=admin->findByUsername(susername.toStdString());

    if(toChange!=0){

        if(ui->basicRadioButton->isChecked()){
            const UtenteBasic* uba = dynamic_cast<const UtenteBasic*>(toChange);
            if(uba){
                QMessageBox err;
                err.setText("L'utente selezionato ha già questo tipo!");
                err.exec();}
            else{
                Username un(toChange->getLogin(), toChange->getPassword());
                Utente* ub=new UtenteBasic(un, *(toChange->getInfo()));
                admin->insert(ub);
                admin->remove(toChange);
                str=str+QString::fromStdString(ub->getName())+QString::fromStdString(" ")+QString::fromStdString(ub->getSurname());
                emit userFound(str);
                QMessageBox msg;
                msg.setText("Cambiamento Avvenuto");
                msg.exec();
            }
        }
        else{
            if(ui->businessRadioButton->isChecked()){
                const UtenteBusiness* ubu = dynamic_cast<const UtenteBusiness*>(toChange);
                if(ubu){
                    QMessageBox err;
                    err.setText("L'utente selezionato ha già questo tipo!");
                    err.exec();}
                else{
                    Username un(toChange->getLogin(), toChange->getPassword());
                    Utente* ub=new UtenteBusiness(un, *(toChange->getInfo()));
                    admin->insert(ub);
                    admin->remove(toChange);
                    str=str+QString::fromStdString(ub->getName())+QString::fromStdString(" ")+QString::fromStdString(ub->getSurname());
                    emit userFound(str);
                    QMessageBox msg;
                    msg.setText("Cambiamento Avvenuto");
                    msg.exec();
                }
            }
            else{
                if(ui->executiveRadioButton->isChecked()){
                    const UtenteExecutive* uex = dynamic_cast<const UtenteExecutive*>(toChange);
                    if(uex){
                        QMessageBox err;
                        err.setText("L'utente selezionato ha già questo tipo!");
                        err.exec();}
                    else{
                        Username un(toChange->getLogin(), toChange->getPassword());
                        Utente* ub=new UtenteExecutive(un, *(toChange->getInfo()));
                        admin->insert(ub);
                        admin->remove(toChange);
                        str=str+QString::fromStdString(ub->getName())+QString::fromStdString(" ")+QString::fromStdString(ub->getSurname());
                        emit userFound(str);
                        QMessageBox msg;
                        msg.setText("Cambiamento Avvenuto");
                        msg.exec();
                    }
                }
                else{
                    QMessageBox err;
                    err.setText(QString::fromStdString("Non hai selezionato il nuovo tipo da convertire"));
                    err.exec();
                }
            }
        }
     }

else{
        QMessageBox msg;
        msg.setText("Nessun Utente Trovato");
        msg.exec();
        emit userNotFound(QString::fromStdString("Nessun Utente Trovato"));}
}


/*
   /////////////////////////////////////////////////////
    DEFINIZIONE SLOTS
   /////////////////////////////////////////////////////
*/

void AdminMainWindow::on_RegisterNewUser_clicked(){
    //connessione per inserimento nuovo utente
    registrationwindow* rw=new registrationwindow(admin);
    rw->show();
}

void AdminMainWindow::on_FindUserButton_clicked(){
   findUser();
}

void AdminMainWindow::on_deleteUserButton_clicked(){
   deleteUser();
}

void AdminMainWindow::on_getAllUsers_clicked(){
   getAllUsers();
}

void AdminMainWindow::on_changeAccountUserButton_clicked(){
   changeAccountType();
}

void AdminMainWindow::on_emptyDbButton_clicked(){
    admin->emptyDB();
    emit userFound("Database Svuotato");
}

void AdminMainWindow::on_closeButton_clicked(){
    emit adClose();
    this->close();
    //viene eliminato perchè al successivo accesso senno avrei ancora tutta la memoria occupata del primo accesso, sprecandola
    delete admin;
}

void AdminMainWindow::on_saveDB_clicked(){
    admin->save();
    emit userFound("Database Salvato");
}

vector<vector<Utente*>::iterator> AdminMainWindow::search(string n, string s){
    return admin->search(n,s);
}
