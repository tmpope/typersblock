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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LevelSelectWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;

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
        label->setGeometry(QRect(560, 30, 181, 51));
        QFont font;
        font.setPointSize(24);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("color: white;\n"
"background-image: url(:/new/images/alpha.png);"));

        retranslateUi(LevelSelectWindow);

        QMetaObject::connectSlotsByName(LevelSelectWindow);
    } // setupUi

    void retranslateUi(QWidget *LevelSelectWindow)
    {
        LevelSelectWindow->setWindowTitle(QApplication::translate("LevelSelectWindow", "Form", 0));
        label->setText(QApplication::translate("LevelSelectWindow", "Level Select", 0));
    } // retranslateUi

};

namespace Ui {
    class LevelSelectWindow: public Ui_LevelSelectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELSELECTWINDOW_H
