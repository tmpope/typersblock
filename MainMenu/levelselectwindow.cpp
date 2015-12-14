#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"
#include "sfmlcanvas.h"
#include <QMessageBox>
#include <QDebug>
#include <iostream>

LevelSelectWindow::LevelSelectWindow(std::string user, std::string pass, QWidget* previous, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectWindow)
{
    ui->setupUi(this);
    ui->label->setText("Welcome, " + QString::fromStdString(user));
    prev = previous;

    userName = user;
    password = pass;

    //Set up music
    if (!music.openFromFile("../MainMenu/Music/Level_Select.ogg"))
    {
        QMessageBox::critical(this, "Error", "Sound files missing!");
    }
    music.setLoop(true);
    //music.play();

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
    this->hide();
    music.stop();
}

void LevelSelectWindow::startGame(int level)
{
    //canvas = new SFMLCanvas(this, QPoint(0, 0), QSize(1366, 768), 10, ui->spinBox->value(), userName, password);
    canvas = new SFMLCanvas(this, QPoint(0, 0), QSize(1366, 768), 10, ui->dvorakButton->isChecked(), level, userName, password);
    connect(canvas, SIGNAL(widgetClosed()), this, SLOT(showMenu()));
    canvas->show();
    canvas->update();
    music.stop();
    setWindowTitle("Typer's Block");
}

void LevelSelectWindow::showEvent(QShowEvent* event)
{
    qDebug() << "Show event called on level select.";
    QWidget::showEvent(event);
    showMenu();
}

/* Called after a game has been finished, or when the user first logs in.
 * Starts the music, and pulls their scores from the server.*/
void LevelSelectWindow::showMenu()
{
    music.play();
    //TODO: Update scores via JSON from server
}

void LevelSelectWindow::on_Level1_clicked()
{
    startGame(1);
}

void LevelSelectWindow::on_Level2_clicked()
{
    startGame(2);
}

void LevelSelectWindow::on_Level3_clicked()
{
    startGame(3);
}

void LevelSelectWindow::on_Level4_clicked()
{
    startGame(4);
}

void LevelSelectWindow::on_Level5_clicked()
{
    startGame(5);
}

void LevelSelectWindow::on_Level6_clicked()
{
    startGame(6);
}

void LevelSelectWindow::on_Level7_clicked()
{
    startGame(7);
}

void LevelSelectWindow::on_Level8_clicked()
{
    startGame(8);
}

void LevelSelectWindow::on_Level9_clicked()
{
    startGame(9);
}
