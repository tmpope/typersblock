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
#include <QtWidgets/QRadioButton>
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
    QPushButton *Level1;
    QPushButton *Level2;
    QPushButton *Level3;
    QPushButton *Level4;
    QPushButton *Level6;
    QPushButton *Level8;
    QPushButton *Level7;
    QPushButton *Level5;
    QPushButton *Level9;
    QLabel *merLabel;
    QLabel *venLable;
    QLabel *earLabel;
    QLabel *marLabel;
    QLabel *satLabel;
    QLabel *jupLabel;
    QLabel *uraLabel;
    QLabel *pluLabel;
    QLabel *nepLabel;
    QRadioButton *radioButton;

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
        startButton->setGeometry(QRect(360, 600, 101, 51));
        startButton->setFont(font1);
        startButton->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(250, 600, 91, 51));
        spinBox->setMinimum(1);
        spinBox->setMaximum(9);
        Level1 = new QPushButton(centralWidget);
        Level1->setObjectName(QStringLiteral("Level1"));
        Level1->setGeometry(QRect(260, 200, 250, 90));
        QFont font2;
        font2.setPointSize(20);
        Level1->setFont(font2);
        Level1->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level2 = new QPushButton(centralWidget);
        Level2->setObjectName(QStringLiteral("Level2"));
        Level2->setGeometry(QRect(260, 300, 250, 90));
        Level2->setFont(font2);
        Level2->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level3 = new QPushButton(centralWidget);
        Level3->setObjectName(QStringLiteral("Level3"));
        Level3->setGeometry(QRect(260, 400, 250, 90));
        Level3->setFont(font2);
        Level3->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level4 = new QPushButton(centralWidget);
        Level4->setObjectName(QStringLiteral("Level4"));
        Level4->setGeometry(QRect(640, 200, 250, 90));
        Level4->setFont(font2);
        Level4->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level6 = new QPushButton(centralWidget);
        Level6->setObjectName(QStringLiteral("Level6"));
        Level6->setGeometry(QRect(640, 400, 250, 90));
        Level6->setFont(font2);
        Level6->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level8 = new QPushButton(centralWidget);
        Level8->setObjectName(QStringLiteral("Level8"));
        Level8->setGeometry(QRect(1020, 300, 250, 90));
        Level8->setFont(font2);
        Level8->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level7 = new QPushButton(centralWidget);
        Level7->setObjectName(QStringLiteral("Level7"));
        Level7->setGeometry(QRect(1020, 200, 250, 90));
        Level7->setFont(font2);
        Level7->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level5 = new QPushButton(centralWidget);
        Level5->setObjectName(QStringLiteral("Level5"));
        Level5->setGeometry(QRect(640, 300, 250, 90));
        Level5->setFont(font2);
        Level5->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        Level9 = new QPushButton(centralWidget);
        Level9->setObjectName(QStringLiteral("Level9"));
        Level9->setGeometry(QRect(1020, 400, 250, 90));
        Level9->setFont(font2);
        Level9->setStyleSheet(QLatin1String("color: white;\n"
"background-color: black;"));
        merLabel = new QLabel(centralWidget);
        merLabel->setObjectName(QStringLiteral("merLabel"));
        merLabel->setGeometry(QRect(160, 200, 90, 90));
        merLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/mercury.jpg")));
        merLabel->setAlignment(Qt::AlignCenter);
        venLable = new QLabel(centralWidget);
        venLable->setObjectName(QStringLiteral("venLable"));
        venLable->setGeometry(QRect(160, 300, 90, 90));
        venLable->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/venus.jpg")));
        venLable->setAlignment(Qt::AlignCenter);
        earLabel = new QLabel(centralWidget);
        earLabel->setObjectName(QStringLiteral("earLabel"));
        earLabel->setGeometry(QRect(160, 400, 90, 90));
        earLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/earth.jpg")));
        earLabel->setAlignment(Qt::AlignCenter);
        marLabel = new QLabel(centralWidget);
        marLabel->setObjectName(QStringLiteral("marLabel"));
        marLabel->setGeometry(QRect(540, 200, 90, 90));
        marLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/mars.jpg")));
        marLabel->setAlignment(Qt::AlignCenter);
        satLabel = new QLabel(centralWidget);
        satLabel->setObjectName(QStringLiteral("satLabel"));
        satLabel->setGeometry(QRect(540, 400, 90, 90));
        satLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/saturn.jpg")));
        satLabel->setAlignment(Qt::AlignCenter);
        jupLabel = new QLabel(centralWidget);
        jupLabel->setObjectName(QStringLiteral("jupLabel"));
        jupLabel->setGeometry(QRect(540, 300, 90, 90));
        jupLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/jupiter.jpg")));
        jupLabel->setAlignment(Qt::AlignCenter);
        uraLabel = new QLabel(centralWidget);
        uraLabel->setObjectName(QStringLiteral("uraLabel"));
        uraLabel->setGeometry(QRect(920, 200, 90, 90));
        uraLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/uranus.jpg")));
        uraLabel->setAlignment(Qt::AlignCenter);
        pluLabel = new QLabel(centralWidget);
        pluLabel->setObjectName(QStringLiteral("pluLabel"));
        pluLabel->setGeometry(QRect(920, 400, 90, 90));
        pluLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/pluto.jpg")));
        pluLabel->setAlignment(Qt::AlignCenter);
        nepLabel = new QLabel(centralWidget);
        nepLabel->setObjectName(QStringLiteral("nepLabel"));
        nepLabel->setGeometry(QRect(920, 300, 90, 90));
        nepLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/images/Images/neptune.jpg")));
        nepLabel->setAlignment(Qt::AlignCenter);
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(170, 510, 101, 41));
        QFont font3;
        font3.setPointSize(18);
        radioButton->setFont(font3);
        radioButton->setStyleSheet(QLatin1String("background-image: url(:/new/images/alpha.png);\n"
"color: white;"));

        retranslateUi(LevelSelectWindow);

        QMetaObject::connectSlotsByName(LevelSelectWindow);
    } // setupUi

    void retranslateUi(QWidget *LevelSelectWindow)
    {
        LevelSelectWindow->setWindowTitle(QApplication::translate("LevelSelectWindow", "Level Select", 0));
        label->setText(QApplication::translate("LevelSelectWindow", "Level Select", 0));
        logOutButton->setText(QApplication::translate("LevelSelectWindow", "Log Out", 0));
        startButton->setText(QApplication::translate("LevelSelectWindow", "Start", 0));
        Level1->setText(QApplication::translate("LevelSelectWindow", "Level 1", 0));
        Level2->setText(QApplication::translate("LevelSelectWindow", "Level 2", 0));
        Level3->setText(QApplication::translate("LevelSelectWindow", "Level 3", 0));
        Level4->setText(QApplication::translate("LevelSelectWindow", "Level 4", 0));
        Level6->setText(QApplication::translate("LevelSelectWindow", "Level 6", 0));
        Level8->setText(QApplication::translate("LevelSelectWindow", "Level 8", 0));
        Level7->setText(QApplication::translate("LevelSelectWindow", "Level 7", 0));
        Level5->setText(QApplication::translate("LevelSelectWindow", "Level 5", 0));
        Level9->setText(QApplication::translate("LevelSelectWindow", "Level 9", 0));
        merLabel->setText(QString());
        venLable->setText(QString());
        earLabel->setText(QString());
        marLabel->setText(QString());
        satLabel->setText(QString());
        jupLabel->setText(QString());
        uraLabel->setText(QString());
        pluLabel->setText(QString());
        nepLabel->setText(QString());
        radioButton->setText(QApplication::translate("LevelSelectWindow", "Dvorak", 0));
    } // retranslateUi

};

namespace Ui {
    class LevelSelectWindow: public Ui_LevelSelectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELSELECTWINDOW_H
