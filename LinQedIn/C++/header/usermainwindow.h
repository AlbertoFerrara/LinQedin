#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include "linqedinclient.h"
#include <QWidget>

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainWindow(LinQedInClient*, QWidget *parent = 0);
    ~UserMainWindow();

private slots:
    void on_findAPersonButton_clicked();
    void on_ShowYourProfileButton_clicked();
    void on_ModifyYourProfileButton_clicked();
    void on_closeButton_clicked();
    void on_addFriendButton_clicked();
    void on_removeANetPersonButton_clicked();
    void on_showAllContact_clicked();
    void on_showAllUsers_clicked();

signals:
    void clClose();

private:
    Ui::UserMainWindow *ui;
    LinQedInClient* client;
    vector<vector<Utente*>::iterator> vettoreIt;
    void findPerson();
    void addFriend();
    void removeFriend();
    void searchInNet();
    void showAllUsers();
};

#endif // USERMAINWINDOW_H
