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
    canvas = new SFMLCanvas(this, QPoint(20, 20), QSize(1296, 728), 10);
    canvas->show();
    canvas->update();
}

LevelSelectWindow::~LevelSelectWindow()
{
    delete ui;
}

void LevelSelectWindow::on_pushButton_clicked()
{
    prev->show();
    this->close();
}
