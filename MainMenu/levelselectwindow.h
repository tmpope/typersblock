#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include <QWidget>
#include "sfmlcanvas.h"

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
    void on_pushButton_clicked();

private:
    Ui::LevelSelectWindow *ui;
    QWidget* prev;
    SFMLCanvas* canvas;
};

#endif // LEVELSELECTWINDOW_H
