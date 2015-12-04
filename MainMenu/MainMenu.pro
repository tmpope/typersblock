#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T12:40:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainMenu
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    levelselectwindow.cpp

HEADERS  += mainwindow.h \
    levelselectwindow.h

FORMS    += mainwindow.ui \
    levelselectwindow.ui

RESOURCES += \
    images.qrc

LIBS += -L../SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += ../SFML/include
DEPENDPATH += ../SFML/include

INCLUDEPATH += ./include
