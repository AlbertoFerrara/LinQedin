#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermainwindow.h"
#include "linqedinadmin.h"
#include "linqedinclient.h"
#include "adminmainwindow.h"
#include "QString"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("LinQedIn - Progetto di Programmazione ad Oggetti a.a. 2014/2015 - Developed by Alberto Ferrara (matr. 1049378) ");    
    ui->statusBar->setStyleSheet("background-color:grey; border-top:1px solid;");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->insertPasswordAdminLineEdit->setEchoMode(QLineEdit::Password);

}


MainWindow::~MainWindow()
{
    delete ui;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

void MainWindow::createUserClient(){
    if(!clientOpen){
        QString user=ui->usernameLineEdit->text();
        QString pass=ui->passwordLineEdit->text();
        Username usern(user.toStdString(), pass.toStdString());
        LinQedInClient* lC=new LinQedInClient(usern);
        if(lC->checkUserClient()){
            UserMainWindow* umw=new UserMainWindow(lC);
            connect(umw, SIGNAL(clClose()), this, SLOT(setBoolC()));
            umw->show();
            clientOpen=true;
        }
        else{
            QMessageBox err;
            err.setText("Utente non valido, RIPROVA");
            err.exec();
        }}
    else{
        QMessageBox err1;
        err1.setText("Utente già loggato!");
        err1.exec();
    }
}

void MainWindow::createAdmin(){
    if(!adminOpen){
        QString pass=ui->insertPasswordAdminLineEdit->text();
        if(pass==QString("password")){
            LinQedInAdmin* lA=new LinQedInAdmin;// qui viene caricato anche il db
            AdminMainWindow* aw=new AdminMainWindow(lA); //gli verrà passato anche il lA.
            connect(aw, SIGNAL(adClose()), this, SLOT(setBoolA()));
            //connect(aw, SIGNAL(), this, SLOT(setBool()));
            aw->show();
            adminOpen=true;
        }
        else{
            QMessageBox err;
            err.setText("Password non corretta!");
            err.exec();
        }}
     else{
            QMessageBox err1;
            err1.setText("Amministratore già loggato!");
            err1.exec();
        }
}

void MainWindow::setBoolA(){
    adminOpen=false;
}

void MainWindow::setBoolC(){
    clientOpen=false;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE SLOTS
   /////////////////////////////////////////////////////
*/

void MainWindow::on_sendUsernamePassword_clicked(){
    createUserClient();
}

void MainWindow::on_sendAdminPassword_clicked(){
    createAdmin();
}


