/********************************************************************************
** Form generated from reading UI file 'levelselectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELSELECTWINDOW_H
#define UI_LEVELSELECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LevelSelectWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *logOutButton;
    QPushButton *startButton;
    QSpinBox *spinBox;

    void setupUi(QWidget *LevelSelectWindow)
    {
        if (LevelSelectWindow->objectName().isEmpty())
            LevelSelectWindow->setObjectName(QStringLiteral("LevelSelectWindow"));
        LevelSelectWindow->resize(1366, 768);
        centralWidget = new QWidget(LevelSelectWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 1366, 768));
        centralWidget->setStyleSheet(QStringLiteral("background-image: url(:/new/images/levelSelectBackground.jpg);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 501, 91));
        QFont font;
        font.setFamily(QStringLiteral("GALACTIC VANGUARDIAN NCV"));
        font.setPointSize(24);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));
        logOutButton = new QPushButton(centralWidget);
        logOutButton->setObjectName(QStringLiteral("logOutButton"));
        logOutButton->setGeometry(QRect(10, 700, 101, 51));
        QFont font1;
        font1.setPointSize(16);
        logOutButton->setFont(font1);
        logOutButton->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(200, 250, 101, 51));
        startButton->setFont(font1);
        startButton->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(50, 250, 91, 51));
        spinBox->setMinimum(1);
        spinBox->setMaximum(9);

        retranslateUi(LevelSelectWindow);

        QMetaObject::connectSlotsByName(LevelSelectWindow);
    } // setupUi

    void retranslateUi(QWidget *LevelSelectWindow)
    {
        LevelSelectWindow->setWindowTitle(QApplication::translate("LevelSelectWindow", "Level Select", 0));
        label->setText(QApplication::translate("LevelSelectWindow", "Level Select", 0));
        logOutButton->setText(QApplication::translate("LevelSelectWindow", "Log Out", 0));
        startButton->setText(QApplication::translate("LevelSelectWindow", "Start", 0));
    } // retranslateUi

};

namespace Ui {
    class LevelSelectWindow: public Ui_LevelSelectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELSELECTWINDOW_H
