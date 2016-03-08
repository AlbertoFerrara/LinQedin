#include "showprofile.h"
#include "ui_showprofile.h"

ShowProfile::ShowProfile(LinQedInClient* l, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowProfile), lC(l)
{
    ui->setupUi(this);
    loadProfile();
}

ShowProfile::~ShowProfile(){
    delete ui;
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE METODI
   /////////////////////////////////////////////////////
*/

void ShowProfile::loadProfile(){
    Info i=*(lC->getInfo());
    QString name=QString::fromStdString(i.getName());
    QString surname=QString::fromStdString(i.getSurname());
    QString email=QString::fromStdString(i.getEmail());
    QString address=QString::fromStdString(i.getAddress());
    QString telNumber=QString::fromStdString(i.getTelNumber());
    QString languages=QString::fromStdString(i.getAllLanguages());
    QString workexp=QString::fromStdString(i.getAllWorkExp());
    QString qualif=QString::fromStdString(i.getAllQualif());
    QString persoExp=QString::fromStdString(i.getAllPersonalExp());
    ui->nomeTextLabel->setText(name);
    ui->cognomeTextLabel->setText(surname);
    ui->emailTextLabel->setText(email);
    ui->AddressTextLabel->setText(address);
    ui->telephonTextLabel->setText(telNumber);
    ui->knownLanguagesText->setText(languages);
    ui->workingSkillsTextBox->setText(workexp);
    ui->qualificatioTextBox->setText(qualif);
    ui->personalExperienceTextBox->setText(persoExp);
}

/*
   /////////////////////////////////////////////////////
    DEFINIZIONE SLOTS
   /////////////////////////////////////////////////////
*/

void ShowProfile::on_closeButton_clicked(){
    this->close();
}


