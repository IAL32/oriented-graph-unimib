#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "user.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRegister_clicked();
    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
    database db;
    QButtonGroup btnGroupGender;

    void setup();
};

#endif // MAINWINDOW_H
