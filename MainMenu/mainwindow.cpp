#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <SFML/Network.hpp>
#include <simpleJSON/JSON.h>
#include <simpleJSON/JSONValue.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Connect buttons to their respective methods.
    connect(ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(ui->newAccountButton, SIGNAL(clicked(bool)), this, SLOT(createAccount()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * Socket must be conneceted before calling this method... may change architecture in a bit.
 */
bool MainWindow::sendPacket(std::string dataString, sf::TcpSocket& socket)
{
    sf::Packet packet;
    packet.append(dataString.c_str(), dataString.length());
    //Send the packet
    if (socket.send(packet) != sf::Socket::Done)
    {
         QMessageBox::critical(this, "Error", "Couldn't contact the server. Try again later.");
         return false;
    }
    return true;
}
/*
 * Listens for a response from the server on the provided socket.
 */
std::string MainWindow::receivePacket(sf::TcpSocket& socket)
{
    //Variables to store information for the response from the server.
    char buffer[512];
    sf::IpAddress responseIp;
    size_t responseSize;

    //Receive data from the server.
    socket.receive(buffer, 512, responseSize);
    socket.disconnect();

    //Turn response into a string, return it.
    return std::string(buffer, responseSize);
}

/*
 * Converts the JSONObject into a formatted string containing all the information, in JSON.
 */
std::string MainWindow::convertJSONtoString(JSONObject data)
{
    //Value to be sent over
    JSONValue* val = new JSONValue(data);
    data.clear();

    //Convert from JSONValue to wstring
    std::wstring wideDataString = val->Stringify();
    delete val;

    //Convert from wstring to string
    std::string dataString;
    dataString.assign(wideDataString.begin(), wideDataString.end());
    //Send the data
    return dataString;
    //sendPacket(dataString);
}

/*
 * Called when the user clicks on the login button. Pulls information from the text fields and attempts to
 * contact the server, providing login information.
 */
void MainWindow::login()
{
    if (ui->userLoginText->toPlainText() == "" || ui->passLoginText->toPlainText() == "")
    {
        //Tell user to input information before trying to login
        QMessageBox::critical(this, "Error", "Please fill out the username and password fields before trying to login.");
        return;
    }

    //Ip equivalent of local host.
    //TODO: Find our server's static IP address.
    sf::IpAddress ip("127.0.0.1");
    sf::TcpSocket socket;

    sf::Socket::Status status = socket.connect(ip, 53000);

    //Pull information the user entered, wrap it in a JSONObject.
    JSONObject data;
    data[L"action"] = new JSONValue(L"0");
    data[L"username"] = new JSONValue(ui->userLoginText->toPlainText().toStdWString());
    data[L"password"] = new JSONValue(ui->passLoginText->toPlainText().toStdWString());

    //Send the packet, after converting the JSON object back to a sendable, properly formatted string.
    if (sendPacket(convertJSONtoString(data), socket))
    {
        //Get a response from the server.
        std::string response = receivePacket(socket);
        qDebug() << QString::fromStdString(response);
        //Do something with the response
    }
}

/*
 * Called when the user clicks on the new account button. Using all the text fields, attempts to contact the server
 * in order to create a new account with the given information.
 */
void MainWindow::createAccount()
{
    //If fields are blank, or the password is less than 8 characters long, print out an error.
    if (ui->firstNameText->toPlainText() == "" || ui->lastNameText->toPlainText() == ""
            || ui->userCreateText->toPlainText() == "" || ui->passCreateText->toPlainText().length() < 8 || ui->classText->toPlainText() == "")
    {
        //Ask for all information
        QMessageBox::critical(this, "Error", "All fields required to create an account. Passwords must be 8 characters or longer.");
        return;
    }

    sf::IpAddress ip("127.0.0.1");
    sf::TcpSocket socket;

    sf::Socket::Status status = socket.connect(ip, 53000);

    //Going to store all our JSON information in here.
    JSONObject data;

    data[L"action"] = new JSONValue(L"1");
    data[L"username"] = new JSONValue(ui->userCreateText->toPlainText().toStdWString());
    data[L"password"] = new JSONValue(ui->passCreateText->toPlainText().toStdWString());
    data[L"firstname"] = new JSONValue(ui->firstNameText->toPlainText().toStdWString());
    data[L"lastname"] = new JSONValue(ui->lastNameText->toPlainText().toStdWString());
    data[L"class"] = new JSONValue(ui->classText->toPlainText().toStdWString());

    if (sendPacket(convertJSONtoString(data), socket))
    {
        //Get a response from the server.
        std::string response = receivePacket(socket);
        qDebug() << QString::fromStdString(response);
        //Do something with the response
    }
}
