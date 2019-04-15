#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(database* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    setup(db);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::setup(database* db) {
    std::list<user> users = db->getUsers();
    std::list<user>::iterator ib, ie;
    int i, j;
    QHeaderView* usersTableHeaderView = ui->usersTable->horizontalHeader();

    // sets column headers
    usersTableHeaderView->setSectionResizeMode(QHeaderView::Stretch);
    ui->usersTable->setColumnCount(user::Attr::COUNT);
    for (i = 0; i < user::Attr::COUNT; i++) {
        switch (i) {
        case user::Attr::PHONENUMBER: {
            // no need to handle the new, as https://doc.qt.io/qt-5/qtablewidget.html#setItem
            // says that the table takes ownership of the item, hence
            // there is no need to do it myself
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Phone number"));
            break;
        }
        case user::Attr::NAME: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Name"));
            break;
        }
        case user::Attr::SURNAME: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Surname"));
            break;
        }
        case user::Attr::GENDER: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Gender"));
            break;
        }
        case user::Attr::BIRTHDAY: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Birthday"));
            break;
        }
        case user::Attr::PASSWORD: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Password"));
            break;
        }
        case user::Attr::EMAIL: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Email"));
            break;
        }
        case user::Attr::ROLE: {
            ui->usersTable->setHorizontalHeaderItem(i, new QTableWidgetItem("Administrator"));
            break;
        }
        default: {
            break;
        }
        }
    }
    // sets user rows
    for (i = 0, ib = users.begin(), ie = users.end(); ib != ie; ++ib, i++) {
        ui->usersTable->insertRow(ui->usersTable->rowCount());
        for (j = 0; j < user::Attr::COUNT; j++) {
            switch (j) {
            case user::Attr::PHONENUMBER: {
                // no need to handle the new, as https://doc.qt.io/qt-5/qtablewidget.html#setItem
                // says that the table takes ownership of the item, hence
                // there is no need to do it myself
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getPhoneNumber()));
                break;
            }
            case user::Attr::NAME: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getName()));
                break;
            }
            case user::Attr::SURNAME: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getSurname()));
                break;
            }
            case user::Attr::GENDER: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getGenderString()));
                break;
            }
            case user::Attr::BIRTHDAY: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getBirthday().toString(user::DEFAULT_DATE_FORMAT)));
                break;
            }
            case user::Attr::PASSWORD: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getPassword()));
                break;
            }
            case user::Attr::EMAIL: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getEmail()));
                break;
            }
            case user::Attr::ROLE: {
                ui->usersTable->setItem(i, j, new QTableWidgetItem(ib->getRoleString()));
                break;
            }
            default: {
                break;
            }
            }
        }
    }
}
