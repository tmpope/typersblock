#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include <QWidget>
#include "sfmlcanvas.h"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "Box2D/Box2D.h"

namespace Ui {
class LevelSelectWindow;
}

class LevelSelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelectWindow(std::string user = "user", std::string pass = "", QWidget* previous = 0, QWidget* parent = 0);
    ~LevelSelectWindow();

private slots:
    void logOut();
    void startGame(int);
    void showEvent(QShowEvent*);
    void showMenu();

    //Makes sure when the level button is clicked, the corret lesson shows up
    void on_Level1_clicked();
    void on_Level2_clicked();
    void on_Level3_clicked();
    void on_Level4_clicked();
    void on_Level5_clicked();
    void on_Level6_clicked();
    void on_Level7_clicked();
    void on_Level8_clicked();
    void on_Level9_clicked();

private:
    Ui::LevelSelectWindow *ui;
    QWidget* prev;
    SFMLCanvas* canvas;
    sf::Music music;
    std::string password;
    std::string userName;
    void getScores();
};

#endif // LEVELSELECTWINDOW_H
