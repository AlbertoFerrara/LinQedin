#ifndef MODIFYPROFILE_H
#define MODIFYPROFILE_H

#include <utente.h>
#include "linqedinclient.h"
#include <QWidget>

namespace Ui {
class ModifyProfile;
}

class ModifyProfile : public QWidget
{
    Q_OBJECT

private slots:
    void on_confirmButton_clicked();

public:
    explicit ModifyProfile(Utente*, QWidget *parent = 0);
    ~ModifyProfile();

private:
    Ui::ModifyProfile *ui;
    Utente* user;
};

#endif // MODIFYPROFILE_H
