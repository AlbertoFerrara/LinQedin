#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sendUsernamePassword_clicked();
    void on_sendAdminPassword_clicked();
    void setBoolA();
    void setBoolC();

private:
    Ui::MainWindow *ui;
    bool clientOpen;
    bool adminOpen;
    void createUserClient();
    void createAdmin();
};

#endif // MAINWINDOW_H
