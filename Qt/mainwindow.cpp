#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup() {
    QString formStyleSheet = "QLineEdit { border-radius: 5px; border: 1px solid lightgray; }";
    // set styles
    QStringList cmbRDateDays;
    QStringList cmbRDateMonths;
    QStringList cmbRDateYears;

//    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

//    setFixedSize(width(), height());
    ui->statusBar->setSizeGripEnabled(false);
    ui->txtRNome->setStyleSheet(formStyleSheet);
    ui->txtRCognome->setStyleSheet(formStyleSheet);
    ui->txtREmailPhone->setStyleSheet(formStyleSheet);
    ui->txtRPassword->setStyleSheet(formStyleSheet);

    for (int i = 1; i <= 31; i++)
        cmbRDateDays << QString::number(i);
    for (int i = 1; i <= 12; i++)
        cmbRDateMonths << QString::number(i);
    for (int i = 1870, currentYear = QDate::currentDate().year(); i <= currentYear; i++)
        cmbRDateYears << QString::number(i);

    ui->cmbRDateDay->insertItems(0, cmbRDateDays);
    ui->cmbRDateMonth->insertItems(0, cmbRDateMonths);
    ui->cmbRDateYear->insertItems(0, cmbRDateYears);

    btnGroupGender.addButton(ui->rdRMale);
    btnGroupGender.addButton(ui->rdRFemale);
    btnGroupGender.setId(ui->rdRMale, user::Gender::MALE);
    btnGroupGender.setId(ui->rdRFemale, user::Gender::FEMALE);
    ui->rdRFemale->setChecked(true);

    db = database(QDir::currentPath().toStdString() + "/data.csv");
}

void MainWindow::on_btnRegister_clicked()
{
    QString name, surname, emailOrPhone, day, month, year, password;
    QDate qBirthday;
    user::Gender gender;
    user u;

    name = ui->txtRNome->text();
    surname = ui->txtRCognome->text();
    emailOrPhone = ui->txtREmailPhone->text();
    day = ui->cmbRDateDay->currentText();
    month = ui->cmbRDateMonth->currentText();
    year = ui->cmbRDateYear->currentText();
    qBirthday = QDate(year.toInt(), month.toInt(), day.toInt());
    gender = btnGroupGender.checkedId() == user::Gender::MALE
            ? user::Gender::MALE
            : user::Gender::FEMALE;
    password = ui->txtRPassword->text();

    if (emailOrPhone.isEmpty()) {
        QMessageBox::critical(
                        this,
                        tr(ui->statusBar->windowTitle().toStdString().c_str()),
                        tr("Email or phone cannot be empty!"));
        return;
    }
    if (!user::isEmail(emailOrPhone.toStdString()) && !user::isPhoneNumber(emailOrPhone.toStdString())) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Email or phone not in a valid format!"));
        return;
    }

    if (day.isEmpty() || month.isEmpty() || year.isEmpty()) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Day, month or year are not selected!"));
        return;
    }

    if (!qBirthday.isValid()) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("The date you selected is not valid!"));
        return;
    }

    if (user::isEmail(emailOrPhone.toStdString())) {
        u.setEmail(emailOrPhone.toStdString());
        u.setPhoneNumber("");
    } else if (user::isPhoneNumber(emailOrPhone.toStdString())) {
        u.setEmail("");
        u.setPhoneNumber(emailOrPhone.toStdString());
    }
    u.setGender(gender);
    u.setName(name.toStdString());
    u.setSurname(surname.toStdString());
    u.setBirthday(qBirthday);
    u.setPassword(password.toStdString());
    u.setRole(user::Role::USER);

    try {
        db.addUser(u);
    } catch(...) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("User with same email or phone number already exists!"));
        return;
    }

    QMessageBox::information(
        this,
        tr(ui->statusBar->windowTitle().toStdString().c_str()),
        tr("Success! You are now registered!"));
}

void MainWindow::on_btnLogin_clicked()
{
    QString phoneOrEmail, password;
    user u;

    phoneOrEmail = ui->txtLEmailPhone->text();
    password = ui->txtLPassword->text();

    if (!user::isPhoneNumber(phoneOrEmail.toStdString()) && !user::isEmail(phoneOrEmail.toStdString())) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Email or phone not in a valid format!"));
        return;
    }

    try {
        std::list<user>::iterator ie = db.getUsers().end();
        u = db.findUserByPhoneNumberOrEmail(phoneOrEmail.toStdString());
        if (u == *ie)
            throw UserNotFoundException();

        if (u.getPassword() != password.toStdString())
            throw CredentialsNotCorrectException();

        if (u.getRole() == user::Role::ADMIN) {
            QMessageBox::information(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Admin"));
        } else
            QMessageBox::information(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Wonderful! You logged in succesfully!"));
    } catch (UserNotFoundException) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("User was not found!"));
        return;
    } catch (CredentialsNotCorrectException) {
        QMessageBox::critical(
                this,
                tr(ui->statusBar->windowTitle().toStdString().c_str()),
                tr("Login credentials are not correct!"));
        return;
    }
}
