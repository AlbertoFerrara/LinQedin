#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include "linqedinadmin.h"

namespace Ui {
class registrationwindow;
}

class registrationwindow : public QWidget
{
    Q_OBJECT

public:
    explicit registrationwindow(LinQedInAdmin* ad, QWidget *parent = 0);
    ~registrationwindow();

private slots:
    void on_sendDataButton_clicked();

signals:
    void newUserCreated(Utente*);

private:
    Ui::registrationwindow *ui;
    LinQedInAdmin* adminR;
    void registerNewUser();
};

#endif // REGISTRATIONWINDOW_H
