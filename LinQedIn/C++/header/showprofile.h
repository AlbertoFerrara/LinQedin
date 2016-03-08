#ifndef SHOWPROFILE_H
#define SHOWPROFILE_H

#include <QWidget>
#include "linqedinclient.h"

namespace Ui {
class ShowProfile;
}

class ShowProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ShowProfile(LinQedInClient*, QWidget *parent = 0);
    ~ShowProfile();

private slots:
    void on_closeButton_clicked();

private:
    Ui::ShowProfile *ui;
    LinQedInClient* lC;
    void loadProfile();
};

#endif // SHOWPROFILE_H
