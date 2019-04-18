#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "user.h"
#include "database.h"
#include "admindialog.h"

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

    void on_label_linkActivated(const QString &link);

    void on_txtLEmailPhone_returnPressed();

    void on_txtLPassword_returnPressed();

private:
    Ui::MainWindow *ui;
    database db;
    QButtonGroup btnGroupGender;
    AdminDialog *myAdminDialog;

    void setup(void);
    void errorDialog(QString error);
    void infoDialog(QString info);
    void showAdminWindow(void);
    void signup(void);
    void login(void);
};

#endif // MAINWINDOW_H
