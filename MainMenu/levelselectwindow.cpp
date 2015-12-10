#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"
#include "sfmlcanvas.h"

LevelSelectWindow::LevelSelectWindow(std::string user, QWidget* previous, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectWindow)
{
    ui->setupUi(this);
    ui->label->setText("Welcome, " + QString::fromStdString(user));
    prev = previous;

    connect(ui->logOutButton, SIGNAL(clicked(bool)), this, SLOT(logOut()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startGame()));
}

LevelSelectWindow::~LevelSelectWindow()
{
    delete ui;
    delete canvas;
}

void LevelSelectWindow::logOut()
{
    prev->show();
    this->close();
}

void LevelSelectWindow::startGame()
{
    canvas = new SFMLCanvas(this, QPoint(0, 0), QSize(1366, 768), 10);
    canvas->show();
    canvas->update();
}
