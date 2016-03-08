#include "showprofilefind.h"
#include "ui_showprofilefind.h"

ShowProfileFind::ShowProfileFind(vector<string> v, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowProfileFind), info(v)
{
    ui->setupUi(this);
    loadData();
}

ShowProfileFind::~ShowProfileFind()
{
    delete ui;
}

void ShowProfileFind::loadData(){
    string tu=info[0];
    if(tu=="Basic"){
        ui->nomeTextLabel_2->setText(QString::fromStdString(info[1]));
        ui->cognomeTextLabel_2->setText(QString::fromStdString(info[2]));
        ui->emailTextLabel_2->setText("Per visualizzare, cambia tipo account");
        ui->AddressTextLabel_2->setText("Per visualizzare, cambia tipo account");
        ui->telephonTextLabel_2->setText("Per visualizzare, cambia tipo account");
        ui->knownLanguagesText_2->setText("Per visualizzare, cambia tipo account");
        ui->workingSkillsTextBox_2->setText("Per visualizzare, cambia tipo account");
        ui->qualificatioTextBox_2->setText("Per visualizzare, cambia tipo account");
        ui->personalExperienceTextBox_2->setText("Per visualizzare, cambia tipo account");
    }
    else{
        if(tu=="Business"){
            ui->nomeTextLabel_2->setText(QString::fromStdString(info[1]));
            ui->cognomeTextLabel_2->setText(QString::fromStdString(info[2]));
            ui->emailTextLabel_2->setText(QString::fromStdString(info[3]));
            ui->AddressTextLabel_2->setText(QString::fromStdString(info[4]));
            ui->telephonTextLabel_2->setText(QString::fromStdString(info[5]));
            ui->knownLanguagesText_2->setText("Per visualizzare, cambia tipo account in Executive");
            ui->workingSkillsTextBox_2->setText("Per visualizzare, cambia tipo account in Executive");
            ui->qualificatioTextBox_2->setText("Per visualizzare, cambia tipo account in Executive");
            ui->personalExperienceTextBox_2->setText("Per visualizzare, cambia tipo account in Executive");
        }
        else{
            if(tu=="Executive"){
                ui->nomeTextLabel_2->setText(QString::fromStdString(info[1]));
                ui->cognomeTextLabel_2->setText(QString::fromStdString(info[2]));
                ui->emailTextLabel_2->setText(QString::fromStdString(info[3]));
                ui->AddressTextLabel_2->setText(QString::fromStdString(info[4]));
                ui->telephonTextLabel_2->setText(QString::fromStdString(info[5]));
                ui->knownLanguagesText_2->setText(QString::fromStdString(info[6]));
                ui->workingSkillsTextBox_2->setText(QString::fromStdString(info[7]));
                ui->qualificatioTextBox_2->setText(QString::fromStdString(info[8]));
                ui->personalExperienceTextBox_2->setText(QString::fromStdString(info[9]));
            }
        }
    }
}

void ShowProfileFind::on_closeButton_clicked(){
    this->close();
}
