/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *passLoginText;
    QPushButton *loginButton;
    QTextEdit *userLoginText;
    QTextEdit *lastNameText;
    QPushButton *newAccountButton;
    QTextEdit *userCreateText;
    QTextEdit *firstNameText;
    QTextEdit *classText;
    QTextEdit *passCreateText;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(920, 585);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-image: url(:/new/images/space_scene_by_felandi.jpg);"));
        passLoginText = new QTextEdit(centralWidget);
        passLoginText->setObjectName(QStringLiteral("passLoginText"));
        passLoginText->setGeometry(QRect(60, 250, 341, 31));
        passLoginText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        passLoginText->setTabChangesFocus(true);
        loginButton = new QPushButton(centralWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(180, 320, 101, 31));
        loginButton->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        userLoginText = new QTextEdit(centralWidget);
        userLoginText->setObjectName(QStringLiteral("userLoginText"));
        userLoginText->setGeometry(QRect(60, 200, 341, 31));
        userLoginText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        userLoginText->setTabChangesFocus(true);
        lastNameText = new QTextEdit(centralWidget);
        lastNameText->setObjectName(QStringLiteral("lastNameText"));
        lastNameText->setGeometry(QRect(710, 100, 151, 31));
        lastNameText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        lastNameText->setTabChangesFocus(true);
        newAccountButton = new QPushButton(centralWidget);
        newAccountButton->setObjectName(QStringLiteral("newAccountButton"));
        newAccountButton->setGeometry(QRect(640, 320, 101, 31));
        newAccountButton->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        userCreateText = new QTextEdit(centralWidget);
        userCreateText->setObjectName(QStringLiteral("userCreateText"));
        userCreateText->setGeometry(QRect(520, 150, 341, 31));
        userCreateText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        userCreateText->setTabChangesFocus(true);
        firstNameText = new QTextEdit(centralWidget);
        firstNameText->setObjectName(QStringLiteral("firstNameText"));
        firstNameText->setGeometry(QRect(520, 100, 151, 31));
        firstNameText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        firstNameText->setTabChangesFocus(true);
        classText = new QTextEdit(centralWidget);
        classText->setObjectName(QStringLiteral("classText"));
        classText->setGeometry(QRect(520, 250, 341, 31));
        classText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        classText->setTabChangesFocus(true);
        passCreateText = new QTextEdit(centralWidget);
        passCreateText->setObjectName(QStringLiteral("passCreateText"));
        passCreateText->setGeometry(QRect(520, 200, 341, 31));
        passCreateText->setStyleSheet(QStringLiteral("background-image: url(:/new/images/Tiny-Grid-Seamless-Patterns-For-Website-Backgrounds.jpg);"));
        passCreateText->setTabChangesFocus(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(870, 110, 47, 13));
        label_3->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(870, 260, 47, 13));
        label_4->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(870, 210, 47, 13));
        label_5->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(870, 160, 47, 13));
        label_6->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(410, 260, 47, 13));
        label_7->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(410, 210, 51, 16));
        label_8->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 241, 61));
        QFont font;
        font.setFamily(QStringLiteral("GALACTIC VANGUARDIAN NCV"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 40, 91, 31));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 920, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Typer's Block", 0));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0));
        newAccountButton->setText(QApplication::translate("MainWindow", "New Account", 0));
        label_3->setText(QApplication::translate("MainWindow", "First/Last", 0));
        label_4->setText(QApplication::translate("MainWindow", "Class", 0));
        label_5->setText(QApplication::translate("MainWindow", "Password", 0));
        label_6->setText(QApplication::translate("MainWindow", "Username", 0));
        label_7->setText(QApplication::translate("MainWindow", "Password", 0));
        label_8->setText(QApplication::translate("MainWindow", "Username", 0));
        label->setText(QApplication::translate("MainWindow", "Typer s Block", 0));
        label_2->setText(QApplication::translate("MainWindow", "'", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
