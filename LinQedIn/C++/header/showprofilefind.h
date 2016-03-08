#ifndef SHOWPROFILEFIND_H
#define SHOWPROFILEFIND_H

#include <QWidget>
#include <vector>
using std::vector;
using std::string;

namespace Ui {
class ShowProfileFind;
}

class ShowProfileFind : public QWidget
{
    Q_OBJECT

public:
    explicit ShowProfileFind(vector<string>, QWidget *parent = 0);
    ~ShowProfileFind();
private slots:
    void on_closeButton_clicked();

private:
    Ui::ShowProfileFind *ui;
    vector<string> info;
    void loadData();
};

#endif // SHOWPROFILEFIND_H
