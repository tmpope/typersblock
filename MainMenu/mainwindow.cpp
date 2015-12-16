#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <SFML/Network.hpp>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Connect buttons to their respective methods.
    connect(ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(ui->newAccountButton, SIGNAL(clicked(bool)), this, SLOT(createAccount()));
    //Set up music
    if (!music.openFromFile("../MainMenu/Music/Login_Music.ogg"))
    {
        QMessageBox::critical(this, "Error", "Sound files missing!");
    }
    music.setLoop(true);
    music.play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete levelSelectWindow;
}

/* Sends a packet with the provided data, over the provided slot. Will pop up an error
 * if the server can't be contacted. */
bool MainWindow::sendPacket(std::string dataString, sf::TcpSocket& socket)
{
    qDebug() << "Sending:" << QString::fromStdString(dataString);
    sf::Packet packet;
    packet << dataString;
    //Send the packet
    if (socket.send(packet) != sf::Socket::Done)
    {
         QMessageBox::critical(this, "Error", "Couldn't contact the server. Try again later.");
         return false;
    }

    return true;
}

/* Listens for a response from the server on the provided socket. */
std::string MainWindow::receivePacket(sf::TcpSocket& socket)
{
    //Store received data here.
    sf::Packet data;
    if (socket.receive(data) != sf::Socket::Done)
    {
        QMessageBox::critical(this, "Error", "No response from server.");
    }
    std::string msg;
    data >> msg;
    qDebug() << "Message received: " << QString::fromStdString(msg);
    socket.disconnect();
    return msg;
}

/* Called when the user clicks on the login button. Pulls information from the text fields and attempts to
 * contact the server, providing login information. */
void MainWindow::login()
{
    /*I've been using this for testing the level select window itself.
    levelSelectWindow = new LevelSelectWindow("Ryan",this);
    levelSelectWindow->show();
    this->hide();
    music.stop();
    return;*/

    if (ui->userLoginText->text() == "" || ui->passLoginText->text() == "")
    {
        //Tell user to input information before trying to login
        QMessageBox::critical(this, "Error", "Please fill out the username and password fields before trying to login.");
        return;
    }

    sf::TcpSocket socket;
    sf::Socket::Status status = connectToServer(socket);

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    //Assemble the JSON to send over.
    writer.StartObject();
    writer.String("action");
    writer.Uint(0);
    writer.String("user");
    writer.String(ui->userLoginText->text().toStdString().c_str());
    writer.String("password");
    writer.String(ui->passLoginText->text().toStdString().c_str());
    writer.EndObject();

    if (sendPacket(s.GetString(), socket))
    {
        enterGame(receivePacket(socket), 0);
    }

    //"{\"action\":0,\"user\":\"newUser\",\"password\":\"notAndre\"}"    <-- example packet
}

/* Called when the user clicks on the new account button. Using all the text fields, attempts to contact the server
 * in order to create a new account with the given information. */

void MainWindow::createAccount()
{
    //If fields are blank, print out an error.
    if (ui->firstNameText->text() == "" || ui->lastNameText->text() == ""
            || ui->userCreateText->text() == "" || ui->passCreateText->text() == "" || ui->classText->text() == "")
    {
        //Ask for all information
        QMessageBox::critical(this, "Error", "All fields required to create an account. Passwords must be 8 characters or longer.");
        return;
    }

    sf::TcpSocket socket;
    sf::Socket::Status status = connectToServer(socket);

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    //Assemble the JSON to send over.
    writer.StartObject();
    writer.String("action");
    writer.Uint(1);
    writer.String("user");
    writer.String(ui->userCreateText->text().toStdString().c_str());
    writer.String("password");
    writer.String(ui->passCreateText->text().toStdString().c_str());
    writer.String("first");
    writer.String(ui->firstNameText->text().toStdString().c_str());
    writer.String("last");
    writer.String(ui->lastNameText->text().toStdString().c_str());
    writer.String("className");
    writer.String(ui->classText->text().toStdString().c_str());
    writer.EndObject();

    if (sendPacket(s.GetString(), socket))
    {
        enterGame(receivePacket(socket), 1);
    }
}

/* Connects a socket to the server. This way, if the server changes,
 * we won't have to update it multiple times in this file. */
sf::Socket::Status MainWindow::connectToServer(sf::TcpSocket& socket)
{
    return socket.connect("waihoilaf.duckdns.org", 53000);
}

/* Tries to enter the game - which is reliant upon the server's response.
 * Shows errors and returns to the login page if the server couldn't authenticate the user. */
void MainWindow::enterGame(std::string response, int action)
{
    rapidjson::Document doc;
    if (doc.Parse(response.c_str()).HasParseError())
    {
        QMessageBox::critical(this, "Error", "Server response corrupted.");
        return;
    }

    if (doc["type"].GetString() == "failure")
    {
        qDebug() << "Failure to login.";
        //Not authenticated correctly.
        QMessageBox::critical(this, "Error", "Invalid credentials.");
        return;
    }

    //Been successful up to this point. Launch level select.
    if (action == 0)
    {
        levelSelectWindow = new LevelSelectWindow(doc["user"].GetString(), ui->passLoginText->text().toStdString(), this);
    }
    else
    {
        levelSelectWindow = new LevelSelectWindow(doc["user"].GetString(), ui->passCreateText->text().toStdString(), this);
    }

    levelSelectWindow->show();
    this->hide();
    music.stop();
}

void MainWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    music.play();
}