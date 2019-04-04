#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup() {
    QRegExp re("^(.*)@(.*)\\.(.*)$");
    QRegExpValidator *emailValidator = new QRegExpValidator(re, this);

    QString formStyleSheet = "QLineEdit { border-radius: 5px; border: 1px solid lightgray; }";

    ui->txtLEmailPhone->setValidator(emailValidator);

    // set styles

    ui->txtRNome->setStyleSheet(formStyleSheet);
    ui->txtREmailPhone->setStyleSheet(formStyleSheet);
    ui->txtRPassword->setStyleSheet(formStyleSheet);

}
