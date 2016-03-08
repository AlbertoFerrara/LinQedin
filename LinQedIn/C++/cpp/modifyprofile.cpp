#include "modifyprofile.h"
#include "ui_modifyprofile.h"
#include <QMessageBox>

ModifyProfile::ModifyProfile(Utente* u, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyProfile),  user(u)
{
    ui->setupUi(this);
    //ui->nameLineEdit->setText(QString::fromStdString(user->getLogin()));
    //ui->surnameLineEdit->setText();
}

void ModifyProfile::on_confirmButton_clicked(){
    QString name=ui->nameLineEdit->text();
    QString surname=ui->surnameLineEdit->text();
    QString password=ui->passwordLineEdit->text();
    QString address=ui->addressLineEdit->text();
    QString telephone=ui->telephoneLineEdit->text();
    QString email=ui->emailLineEdit->text();

    if(name.size()!=0)
        user->setName(name.toStdString());
    if(surname.size()!=0)
        user->setSurname(surname.toStdString());
    if(address.size()!=0)
        user->setAddress(address.toStdString());
    if(telephone.size()!=0)
        user->setTelephone(telephone.toStdString());
    if(email.size()!=0)
        user->setEmail(email.toStdString());
    if(password.size()!=0)
        user->setPassword(password.toStdString());

    if(ui->experienceCheckBox->isChecked()){
           QString experience=ui->experienceTextEdit->toPlainText();
           if(experience.size()!=0)
               user->addWorkExp(experience.toStdString());
           else{
               QMessageBox err;
               err.setText("Campo dati esperienze vuoto!");
               err.exec();
           }

    }
    if(ui->qualificationCheckBox->isChecked()){
           QString qualification=ui->qualificationTextEdit->toPlainText();
           if(qualification.size()!=0)
               user->addQualif(qualification.toStdString());
           else{
               QMessageBox err;
               err.setText("Campo dati esperienze vuoto!");
               err.exec();
           }
    }
    if(ui->personalExperienceCheckBox->isChecked()){
           QString personal=ui->personalTextEdit->toPlainText();
           if(personal.size()!=0)
               user->addPersExp(personal.toStdString());
           else{
               QMessageBox err;
               err.setText("Campo dati esperienze vuoto!");
               err.exec();
           }
    }

    //Gestione inserimento nuove lingue

    if(ui->italianLanguageCheckBox->isChecked()){
        user->addLanguages("Italiano");
    }
    if(ui->englishLanguageCheckBox->isChecked()){
        user->addLanguages("Inglese");
    }
    if(ui->frenchLanguageCheckBox->isChecked()){
        user->addLanguages("Francese");
    }
    if(ui->germanLanguageCheckBox->isChecked()){
        user->addLanguages("Tedesco");
    }
    if(ui->portogheseLanguageCheckBox->isChecked()){
        user->addLanguages("Portoghese");
    }
    if(ui->japaneseLanguageCheckBox->isChecked()){
        user->addLanguages("Giapponese");
    }
    if(ui->spanishLanguageCheckBox->isChecked()){
        user->addLanguages("Spagnolo");
    }
    if(ui->otherLanguagesCheckBox->isChecked()){
        QString otherL=ui->otherLanguagesTextLine->text();
        if(otherL.size()!=0){
            user->addLanguages(otherL.toStdString());
            QMessageBox mess;
            mess.setText("Modifica avvenuta con successo!");
            mess.exec();
            this->close();
        }
        else{
            QMessageBox err;
            err.setText("Non hai inserito una lingua in 'altro'");
            err.exec();}
    }
    else{
        QMessageBox mess;
        mess.setText("Modifica avvenuta con successo!");
        mess.exec();
        this->close();
    }
}

ModifyProfile::~ModifyProfile()
{
    delete ui;
}
