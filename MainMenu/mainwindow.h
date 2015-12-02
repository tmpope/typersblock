#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SFML/Network.hpp>
#include <simpleJSON/JSON.h>
#include <simpleJSON/JSONValue.h>
#include <levelselectwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void login();
    void createAccount();

private:
    Ui::MainWindow *ui;
    //Sends the given packet over the given socket.
    bool sendPacket(std::string dataString, sf::TcpSocket& socket);
    //Receives a packet, turns in into a string, and returns it.
    std::string receivePacket(sf::TcpSocket& socket);
    //Converts a JSONObject to a string, which can then be sent over a socket.
    std::string convertJSONtoString(JSONObject data);
    LevelSelectWindow* levelSelectWindow;
};

#endif // MAINWINDOW_H
