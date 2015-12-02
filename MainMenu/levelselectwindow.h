#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include <QWidget>

namespace Ui {
class LevelSelectWindow;
}

class LevelSelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelectWindow(QWidget *parent = 0);
    ~LevelSelectWindow();

private:
    Ui::LevelSelectWindow *ui;
};

#endif // LEVELSELECTWINDOW_H
