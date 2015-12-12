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
    explicit LevelSelectWindow(std::string user = "user", QWidget* previous = 0, QWidget* parent = 0);
    ~LevelSelectWindow();

private slots:
    void logOut();
    void startGame();
    void showEvent(QShowEvent*);
    void showMenu();

private:
    Ui::LevelSelectWindow *ui;
    QWidget* prev;
    SFMLCanvas* canvas;
    sf::Music music;
};

#endif // LEVELSELECTWINDOW_H
