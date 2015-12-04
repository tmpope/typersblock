#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"

LevelSelectWindow::LevelSelectWindow(std::string user, QWidget* previous, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectWindow)
{
    ui->setupUi(this);
    ui->label->setText("Welcome, " + QString::fromStdString(user));
    prev = previous;
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
