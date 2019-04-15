#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
}

MainWindow::~MainWindow()
{
    delete myAdminDialog;
    delete ui;
}

void MainWindow::setup() {
    QString formStyleSheet = "QLineEdit { border-radius: 5px; border: 1px solid lightgray; }";
    // set styles
    QStringList cmbRDateDays;
    QStringList cmbRDateMonths;
    QStringList cmbRDateYears;

    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

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

    db = database(QDir::currentPath() + "/data.csv");
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
        errorDialog("Email or phone cannot be empty!");
        return;
    }

    try {
        if (user::isEmail(emailOrPhone)) {
            u.setEmail(emailOrPhone);
            u.setPhoneNumber("");
        } else if (user::isPhoneNumber(emailOrPhone)) {
            u.setEmail("");
            u.setPhoneNumber(emailOrPhone);
        }
        u.setGender(gender);
        u.setName(name);
        u.setSurname(surname);
        u.setBirthday(qBirthday);
        u.setPassword(password);
        u.setRole(user::Role::USER);

        db.addUser(u);
        infoDialog("Success! You are now registered!");

    } catch(UserAlreadyRegisteredException) {
        errorDialog("User with same email or phone number already exists!");
    } catch (EmailFormatNotValidException) {
        errorDialog("Email or phone not in a valid format!");
    } catch (PhoneNumberFormatNotValidException) {
        errorDialog("Email or phone not in a valid format!");
    } catch (DateNotValidException) {
        errorDialog("The date you selected is not valid!");
    }
}

void MainWindow::on_btnLogin_clicked()
{
    QString phoneOrEmail, password;
    user u;

    phoneOrEmail = ui->txtLEmailPhone->text();
    password = ui->txtLPassword->text();

    if (phoneOrEmail.isEmpty()) {
        errorDialog("Email or phone cannot be empty!");
        return;
    }

    try {
        u = db.login(phoneOrEmail, password);
        if (u.getRole() == user::Role::ADMIN) {
            showAdminWindow();
        } else {
            infoDialog("Wonderful! You logged in succesfully!");
        }
    } catch(EmailFormatNotValidException) {
        errorDialog("Email or number not in a valid format!");
    } catch (PhoneNumberFormatNotValidException) {
        errorDialog("Email or number not in a valid format!");
    } catch (UserNotFoundException) {
        errorDialog("User was not found!");
        return;
    } catch (CredentialsNotCorrectException) {
        errorDialog("Login credentials are not correct!");
        return;
    }
}

void MainWindow::on_label_linkActivated(const QString &link)
{
    QString input = link; // just so it doesn't give me the warning
    input = QInputDialog::getText(
                this,
                "Password recovery",
                "Insert yout email:");

    if (input.isEmpty())
        return;

    try {
        user u = db.findUserByEmail(input);
        infoDialog("Email with password recovery steps has been sent!");
    } catch(EmailFormatNotValidException) {
        errorDialog("Email not in a valid format!");
    } catch(UserNotFoundException) {
        errorDialog("User with that email has not been found!");
    }
}

void MainWindow::errorDialog(QString error) {
    QMessageBox::critical(this, ui->statusBar->windowTitle(), error);
}

void MainWindow::infoDialog(QString info) {
    QMessageBox::information(this, ui->statusBar->windowTitle(), info);
}

void MainWindow::showAdminWindow() {
    myAdminDialog = new AdminDialog(&db, this);
    myAdminDialog->exec();
}
