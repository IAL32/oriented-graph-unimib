/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QLineEdit *txtLEmailPhone;
    QLabel *lblLEmailPhone;
    QLabel *lblLPassword;
    QLineEdit *txtLPassword;
    QPushButton *btnLogin;
    QLabel *label;
    QWidget *widget_2;
    QLineEdit *txtRNome;
    QLineEdit *txtCognome;
    QLineEdit *txtREmailPhone;
    QLineEdit *txtRPassword;
    QComboBox *cmbDateDay;
    QComboBox *cmbDateMonth;
    QComboBox *cmbDateYear;
    QRadioButton *rdWoman;
    QRadioButton *rdMan;
    QPushButton *btnRegister;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(528, 354);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 531, 101));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(32, 74, 135, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(48, 111, 203, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(40, 92, 169, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(16, 37, 67, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(21, 49, 90, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        QBrush brush6(QColor(238, 238, 236, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        QBrush brush8(QColor(143, 164, 195, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush8);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        QBrush brush10(QColor(238, 238, 236, 128));
        brush10.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        QBrush brush11(QColor(0, 0, 0, 128));
        brush11.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        widget->setPalette(palette);
        widget->setCursor(QCursor(Qt::ArrowCursor));
        widget->setAutoFillBackground(true);
        txtLEmailPhone = new QLineEdit(widget);
        txtLEmailPhone->setObjectName(QString::fromUtf8("txtLEmailPhone"));
        txtLEmailPhone->setGeometry(QRect(10, 40, 141, 25));
        lblLEmailPhone = new QLabel(widget);
        lblLEmailPhone->setObjectName(QString::fromUtf8("lblLEmailPhone"));
        lblLEmailPhone->setGeometry(QRect(10, 10, 114, 20));
        lblLPassword = new QLabel(widget);
        lblLPassword->setObjectName(QString::fromUtf8("lblLPassword"));
        lblLPassword->setGeometry(QRect(190, 10, 65, 17));
        txtLPassword = new QLineEdit(widget);
        txtLPassword->setObjectName(QString::fromUtf8("txtLPassword"));
        txtLPassword->setGeometry(QRect(190, 40, 141, 25));
        txtLPassword->setEchoMode(QLineEdit::Password);
        btnLogin = new QPushButton(widget);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(410, 30, 89, 40));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 71, 291, 17));
        QPalette palette1;
        QBrush brush12(QColor(186, 189, 182, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        QBrush brush13(QColor(220, 222, 218, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush13);
        QBrush brush14(QColor(93, 94, 91, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush14);
        QBrush brush15(QColor(124, 126, 121, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush15);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush11);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush15);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        label->setPalette(palette1);
        label->setCursor(QCursor(Qt::PointingHandCursor));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 100, 521, 181));
        txtRNome = new QLineEdit(widget_2);
        txtRNome->setObjectName(QString::fromUtf8("txtRNome"));
        txtRNome->setGeometry(QRect(10, 10, 251, 30));
        txtCognome = new QLineEdit(widget_2);
        txtCognome->setObjectName(QString::fromUtf8("txtCognome"));
        txtCognome->setGeometry(QRect(270, 10, 231, 30));
        txtREmailPhone = new QLineEdit(widget_2);
        txtREmailPhone->setObjectName(QString::fromUtf8("txtREmailPhone"));
        txtREmailPhone->setGeometry(QRect(10, 50, 491, 30));
        txtREmailPhone->setStyleSheet(QString::fromUtf8(""));
        txtRPassword = new QLineEdit(widget_2);
        txtRPassword->setObjectName(QString::fromUtf8("txtRPassword"));
        txtRPassword->setGeometry(QRect(10, 90, 491, 30));
        cmbDateDay = new QComboBox(widget_2);
        cmbDateDay->setObjectName(QString::fromUtf8("cmbDateDay"));
        cmbDateDay->setGeometry(QRect(10, 130, 86, 25));
        cmbDateMonth = new QComboBox(widget_2);
        cmbDateMonth->setObjectName(QString::fromUtf8("cmbDateMonth"));
        cmbDateMonth->setGeometry(QRect(100, 130, 86, 25));
        cmbDateYear = new QComboBox(widget_2);
        cmbDateYear->setObjectName(QString::fromUtf8("cmbDateYear"));
        cmbDateYear->setGeometry(QRect(190, 130, 86, 25));
        rdWoman = new QRadioButton(widget_2);
        rdWoman->setObjectName(QString::fromUtf8("rdWoman"));
        rdWoman->setGeometry(QRect(290, 130, 112, 23));
        rdMan = new QRadioButton(widget_2);
        rdMan->setObjectName(QString::fromUtf8("rdMan"));
        rdMan->setGeometry(QRect(400, 130, 112, 23));
        btnRegister = new QPushButton(centralWidget);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setGeometry(QRect(10, 280, 510, 30));
        QPalette palette2;
        QBrush brush16(QColor(78, 154, 6, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush16);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush16);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush16);
        QBrush brush17(QColor(190, 190, 190, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush17);
        btnRegister->setPalette(palette2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 528, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lblLEmailPhone->setText(QApplication::translate("MainWindow", "Email o Telefono", nullptr));
        lblLPassword->setText(QApplication::translate("MainWindow", "Password", nullptr));
        btnLogin->setText(QApplication::translate("MainWindow", "Accedi", nullptr));
        label->setText(QApplication::translate("MainWindow", "Non ricordi come accedere al tuo account?", nullptr));
        txtRNome->setPlaceholderText(QApplication::translate("MainWindow", "Nome", nullptr));
        txtCognome->setPlaceholderText(QApplication::translate("MainWindow", "Cognome", nullptr));
        txtREmailPhone->setPlaceholderText(QApplication::translate("MainWindow", "Numero di cellulare o e-mail", nullptr));
        txtRPassword->setPlaceholderText(QApplication::translate("MainWindow", "Password", nullptr));
        rdWoman->setText(QApplication::translate("MainWindow", "Donna", nullptr));
        rdMan->setText(QApplication::translate("MainWindow", "Uomo", nullptr));
        btnRegister->setText(QApplication::translate("MainWindow", "Iscriviti", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
