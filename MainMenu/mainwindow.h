#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
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
    void showEvent(QShowEvent *);

private:
    Ui::MainWindow *ui;
    //Sends the given packet over the given socket.
    bool sendPacket(std::string dataString, sf::TcpSocket& socket);
    //Receives a packet, turns in into a string, and returns it.
    std::string receivePacket(sf::TcpSocket& socket);
    LevelSelectWindow* levelSelectWindow;
    sf::Socket::Status connectToServer(sf::TcpSocket& socket);
    void enterGame(std::string response, int action);
    sf::Music music;
};

#endif // MAINWINDOW_H
