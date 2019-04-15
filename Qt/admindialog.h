#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <list>
#include "user.h"
#include "database.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(database* db = nullptr, QWidget *parent = nullptr);
    ~AdminDialog();

private:
    Ui::AdminDialog *ui;
    database* db;
    void setup(database* db);
};

#endif // ADMINDIALOG_H
