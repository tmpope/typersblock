#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"
#include "sfmlcanvas.h"
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

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
    canvas = new SFMLCanvas(this, QPoint(0, 0), QSize(1366, 768), 10, ui->dvorakButton->isChecked(), level, userName, password);
    connect(canvas, SIGNAL(widgetClosed()), this, SLOT(showMenu()));
    canvas->show();
    canvas->update();
    music.stop();
    setWindowTitle("Typer's Block");
}

void LevelSelectWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    showMenu();
}

/* Called after a game has been finished, or when the user first logs in.
 * Starts the music, and pulls their scores from the server.*/
void LevelSelectWindow::showMenu()
{
    music.play();
    getScores();
}

/* Gets the scores for each completed level, disables buttons for levels the user can't yet do.
 * Retrieves the scores by calling the login function again. */
void LevelSelectWindow::getScores()
{
    //TODO: SEND SCORES THROUGH JSON HERE
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    //Assemble the JSON to send over.
    writer.StartObject();
    writer.String("action");
    writer.Uint(0);
    writer.String("user");
    writer.String(userName.c_str());
    writer.String("password");
    writer.String(password.c_str());
    writer.EndObject();

    qDebug() << QString::fromStdString(s.GetString());

    //Connect to the server
    sf::TcpSocket socket;
    socket.connect("waihoilaf.duckdns.org", 53000);

    //Store data in a packet
    sf::Packet packet;
    packet << s.GetString();
    //Send the packet
    if (socket.send(packet) != sf::Socket::Done)
    {
         QMessageBox::critical(this, "Error", "Couldn't contact the server. Try again later.");
    }
    //Recieve a response
    sf::Packet data;
    if (socket.receive(data) != sf::Socket::Done)
    {
        QMessageBox::critical(this, "Error", "No response from server.");
    }
    std::string msg;
    data >> msg;
    qDebug() << "Message received: " << QString::fromStdString(msg);
    socket.disconnect();

    rapidjson::Document doc;
    //Parse information sent back.
    if (doc.Parse(msg.c_str()).HasParseError())
    {
        QMessageBox::critical(this, "Error", "Server response corrupted.");
    }
    if (doc["type"].GetString() == "failure")
    {
        //Not authenticated correctly.
        QMessageBox::critical(this, "Error", "Couldn't retrieve scores correctly.");
    }
    const rapidjson::Value& array = doc["scores"];
    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        //Enable the button for level (index + 1) + 1. AKA, the next level the user should theoretically be able to do.
        //We really should've used an array...
        switch(i)
        {
        case 0:
            ui->Level2->setEnabled(true);
            break;
        case 1:
            ui->Level3->setEnabled(true);
            break;
        case 2:
            ui->Level4->setEnabled(true);
            break;
        case 3:
            ui->Level5->setEnabled(true);
            break;
        case 4:
            ui->Level6->setEnabled(true);
            break;
        case 5:
            ui->Level7->setEnabled(true);
            break;
        case 6:
            ui->Level8->setEnabled(true);
            break;
        case 7:
            ui->Level9->setEnabled(true);
            break;
        }
    }
}


/*
 *  Ugly code following - buttons can't provide a value in their slot, so for a short hand way to do this, we used the "go to slot" function on each button.
 *  Each button provides the level that it stands for.
 */
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
