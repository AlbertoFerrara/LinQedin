#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include "utente.h"
#include "linqedinadmin.h"
#include <QWidget>

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AdminMainWindow(LinQedInAdmin* , QWidget *parent = 0);
    ~AdminMainWindow();
    vector<vector<Utente*>::iterator> search(string, string);

private slots:
    void on_RegisterNewUser_clicked();
    void on_FindUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_changeAccountUserButton_clicked();
    void on_emptyDbButton_clicked();
    void on_closeButton_clicked();   
    void on_saveDB_clicked();
    void on_getAllUsers_clicked();
    void updateText(QString);

signals:
    void newUserAdded();
    void userFound(QString);
    void userNotFound(QString);
    void adClose();

private:
    Ui::AdminMainWindow *ui;
    LinQedInAdmin* admin;
    //nella ricerca, serve per salvare gli iteratori ai risultati della ricerca
    vector<vector<Utente*>::iterator> vettoreIt;
    void clearTextBox();
    void printInfo(QString s);
    void findUser();
    void deleteUser();
    void getAllUsers();
    void changeAccountType();
    void clearTable();
};

#endif // ADMINMAINWINDOW_H
