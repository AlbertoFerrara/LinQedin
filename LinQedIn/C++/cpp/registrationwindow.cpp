#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "linqedinclient.h"
#include "username.h"
#include "utente.h"
#include "utentebasic.h"
#include "utentebusiness.h"
#include "utenteexecutive.h"
#include <QMessageBox>

registrationwindow::registrationwindow(LinQedInAdmin* ad, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrationwindow), adminR(ad)
{
    ui->setupUi(this);
    ui->newPasswordTextLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordTextLineEdit->setEchoMode(QLineEdit::Password);
    QRegExp reName("^[ A-Z | a-z ]{20}$");
    QRegExp reNumber("^[ 0-9]{10}$");
    //QRegExp reEmail("^[ A-Z | a-z | . ]{*} [@]{1} [A-Z | a-z]{5} [.]{1} [com | it | es | gb]{1}");
    QRegExpValidator* validatorName=new QRegExpValidator(reName, 0);
    QRegExpValidator* validatorNumber=new QRegExpValidator(reNumber, 0);
    //QRegExpValidator* validatorEmail=new QRegExpValidator(reEmail, 0);
    ui->newNameTextLineEdit->setValidator(validatorName);
    ui->newSurnameTextLineEdit->setValidator(validatorName);
    ui->telephonNumberTextLineEdit->setValidator(validatorNumber);
    //ui->emailTextLineEdit->setValidator(validatorEmail);
}

registrationwindow::~registrationwindow()
{
    delete ui;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

void registrationwindow::registerNewUser(){
    //creazione nuovo utente
    QString name=ui->newNameTextLineEdit->text();
    QString surname=ui->newSurnameTextLineEdit->text();
    QString username=ui->newUsernameTextLineEdit->text();
    QString password=ui->newPasswordTextLineEdit->text();
    QString confirmPassword=ui->confirmPasswordTextLineEdit->text();
    QString address=ui->addressTextLineEdit->text();
    QString telephon=ui->telephonNumberTextLineEdit->text();
    QString email=ui->emailTextLineEdit->text();

    ui->nameMessageLabel->setText("");
    ui->surnameMessageLabel->setText("");
    ui->usernameMessageLabel->setText("");
    ui->passwordMessageLabel->setText("");
    ui->confirmPasswordMessageLabel->setText("");
    ui->addressMessageLabel->setText("");
    ui->telephonMessageLabel->setText("");
    ui->emailMessageLabel->setText("");

    if(!name.size() || !surname.size() || !username.size() || !password.size() ||
            !address.size() || !telephon.size() || !email.size()){
        if(!name.size()){
            ui->nameMessageLabel->setText("Obbligatorio");
        }
        if(!surname.size()){
            ui->surnameMessageLabel->setText("Obbligatorio");
        }
        if(!username.size()){
            ui->usernameMessageLabel->setText("Obbligatorio");
        }
        if(!password.size()){
            ui->passwordMessageLabel->setText("Obbligatorio");
        }
        if(!confirmPassword.size()){
            ui->confirmPasswordMessageLabel->setText("Obbligatorio");
        }
        if(!address.size()){
            ui->addressMessageLabel->setText("Obbligatorio");
        }
        if(!telephon.size()){
            ui->telephonMessageLabel->setText("Obbligatorio");
        }
        if(!email.size()){
            ui->emailMessageLabel->setText("Obbligatorio");
        }
        QMessageBox err0;
        err0.setText("Manca qualche campo dati obbligatorio!");
        err0.exec();}
    else{

            if(!(ui->BasicButton->isChecked()) && !(ui->BusinessButton->isChecked()) && !(ui->ExecutiveButton->isChecked())){
                QMessageBox err2;
                err2.setText("Non hai scelto il tipo di account!");
                err2.exec();
            }
            else{
                if(password!=confirmPassword){
                    QMessageBox err3;
                    err3.setText("La conferma password non corrisponde");
                    err3.exec();
                }
                else{
                    string susername=username.toStdString();
                    string spassword=password.toStdString();
                    Username usernameClient(susername, spassword);

                    if(adminR->checkUsername(usernameClient)){ //funzione per controllo username univoco
                        string sname=name.toStdString();
                        string ssurname=surname.toStdString();

                        string saddress=address.toStdString();
                        string stelephon=telephon.toStdString();
                        string semail=email.toStdString();


                        if(ui->BasicButton->isChecked()){
                            Info inf(sname, ssurname, saddress, stelephon, semail);
                            Utente* user=new UtenteBasic(usernameClient, inf);
                            //devo aggiungerlo del DB dell'admin
                            adminR->insert(user);}
                        else{
                             if(ui->BusinessButton->isChecked()){
                                 Info inf(sname, ssurname, saddress, stelephon, semail);
                                 Utente* user=new UtenteBusiness(usernameClient, inf);
                                 adminR->insert(user);
                             }
                             else{
                                 if(ui->ExecutiveButton->isChecked()){
                                     Info inf(sname, ssurname, saddress, stelephon, semail);
                                     Utente* user=new UtenteExecutive(usernameClient, inf);
                                     adminR->insert(user);}}
                        }


                      QMessageBox registrationMess;
                      QObject::connect(&registrationMess, SIGNAL(destroyed()), this, SLOT(close()));
                      registrationMess.setText("Registrazione avvenuta con successo!");
                      registrationMess.exec();
                     /*emit newUserAdded();*/}
                    else{
                            QMessageBox err1;
                            err1.setText("Username già esistente!");
                            err1.exec();}
                    }}}
}


/*
   /////////////////////////////////////////////////////
    DEFINIZIONE SLOTS
   /////////////////////////////////////////////////////
*/

void registrationwindow::on_sendDataButton_clicked(){
    registerNewUser();
}
