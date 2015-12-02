#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>

#include <vector>

#include "writer.h"
#include "stringbuffer.h"
#include "reader.h"
#include "document.h"
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

int mySQLexample(void);

bool validate(std::string user, std::string pass) {
    return user == "tpope" && pass == "pass123";
}

int getScore(std::string user, int level) {
    return 3;
}

std::string generateResponse(std::string user, std::string pass)
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    mySQLexample();
    
    if (validate(user, pass))
    {
        writer.StartObject();
        writer.String("type");
        writer.String("success");
        writer.String("user");
        writer.String(user.c_str());
        writer.String("level");
        writer.Uint(1);
        writer.String("id");
        writer.Uint(0);
        writer.String("scores");
        writer.StartArray();
        for (unsigned i = 0; i < 3; i++)
            writer.Uint(getScore(user, i));
        writer.EndArray();
        writer.EndObject();
        return s.GetString();//"Valid login for user " + user;
    }
    else
    {
        return "Invalid username password combination";
    }
    return s.GetString();
}

std::string generateResponse(std::string user, std::string pass, std::string first, std::string last, std::string className)
{
    //TODO actually do what it should
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    mySQLexample();
    
    if (validate(user, pass))
    {
        writer.StartObject();
        writer.String("type");
        writer.String("success");
        writer.String("user");
        writer.String(user.c_str());
        writer.String("level");
        writer.Uint(1);
        writer.String("id");
        writer.Uint(0);
        writer.String("scores");
        writer.StartArray();
        for (unsigned i = 0; i < 3; i++)
            writer.Uint(getScore(user, i));
        writer.EndArray();
        writer.EndObject();
        return s.GetString();//"Valid login for user " + user;
    }
    else
    {
        return "Invalid username password combination";
    }
    return s.GetString();
}

void process(std::string msg, sf::TcpSocket* client) {
    std::cout << "Processing..." << std::endl;
    rapidjson::Document document;
    if (document.Parse(msg.c_str()).HasParseError())
    {
        std::cout << "JSON ERROR" << std::endl;
        return;
    }
    int action = document["action"].GetInt();
    std::string user;
    std::string pass;
    std::string first;
    std::string last;
    std::string className;
    std::cout << "action : " << action << std::endl;
    sf::Packet packet;
    switch(action){
        case 0  : //login
            user = document["user"].GetString();
            pass = document["password"].GetString();
            std::cout << "user : " << user << std::endl;
            packet << generateResponse(user, pass);
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            break; //optional
        case 1  : //create user
            user = document["user"].GetString();
            pass = document["password"].GetString();
            first = document["first"].GetString();
            last = document["last"].GetString();
            className = document["className"].GetString();
            std::cout << "user : " << user << std::endl;
            packet << generateResponse(user, pass, first, last, className);
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            break; //optional
        case 2  : //get key mapping
            std::cout << "Keymapping" << std::endl;
            break;
      
        // you can have any number of case statements.
        default : //Optional
            packet << "Invalid Action";
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            break;


    }
}


// //Sends a packet to the client, using the given data. 
// //The data should have been encoded in JSON before being sent.
// static void sendPacket(std::string dataString, sf::TcpSocket* socket)
// {
//     std::cout << dataString << std::endl;
//     //Set up ip socket and packet
//     // sf::IpAddress ip("127.0.0.1");
//     sf::Packet packet;
//     //Connect to the server
//     // sf::Socket::Status status = socket->connect(ip, 53000);

//     //Attach our information to the packet
//     packet.append(dataString.c_str(), dataString.length());
//     //Send the packet
//     if (socket->send(packet) != sf::Socket::Done)
//     {
//         std::cout << "Error occurred while sending a packet." << std::endl;
//     }
//     //Transmit over; disconnect.
//     // std::cout << "Socket disconnected." << std::endl;
// }

int mySQLexample(void)
{
std::cout << std::endl;
std::cout << "Running 'SELECT 'Hello World!' AS _message'..." << std::endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("waihoilaf.duckdns.org", "typerblock", "TyPeRbL0(k");
  /* Connect to the MySQL test database */
  stmt = con->createStatement();
  stmt->execute("USE TyperBlock");
  res = stmt->executeQuery("SELECT * FROM user_table");
  std::cout << "Done." << std::endl;

  while (res->next()) {
    std::cout << "Got some stuff.";
    /* Access column data by alias or column name */
    //std::cout << res->getString("_message") << std::endl;
    //std::cout << "\t... MySQL says it again: ";
    /* Access column fata by numeric offset, 1 is the first column */
    //std::cout << res->getString(1) << std::endl;
  }
  delete res;
  delete stmt;
  delete con;

} catch (sql::SQLException &e) {
  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}

std::cout << std::endl;

return EXIT_SUCCESS;
}

int main(int, char const**)

{

    sf::TcpListener listener;

    if (listener.listen(53000) != sf::Socket::Done)

    {

        // error...

    }

    // Create a list to store the future clients

    std::vector<sf::TcpSocket*> clients;

    // Create a selector

    sf::SocketSelector selector;

    // Add the listener to the selector

    selector.add(listener);

    // Endless loop that waits for new connections

    while (1)

    {

        // Make the selector wait for data on any socket

        if (selector.wait())

        {

            // Test the listener

            if (selector.isReady(listener))

            {

                // The listener is ready: there is a pending connection

                sf::TcpSocket* client = new sf::TcpSocket;

                if (listener.accept(*client) == sf::Socket::Done)

                {

                    // Add the new client to the clients list

                    clients.push_back(client);

                    // Add the new client to the selector so that we will

                    // be notified when he sends something

                    selector.add(*client);

                }

                else

                {

                    // Error, we won't get a new connection, delete the socket

                    delete client;

                }

            }

            else

            {

                // The listener socket is not ready, test all other sockets (the clients)

                for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)

                {

                    sf::TcpSocket& client = **it; // reference to the actual socket 1st * for it dereference second for pointer

                    if (selector.isReady(client))

                    {

                        sf::Packet packet;

                        if (client.receive(packet) == sf::Socket::Done)

                        {

                            // The client has sent some data, we can receive it

                            std::string msg;

                            packet >> msg;

                            process(msg, &client);

                            std::cout << "Msg received: " << msg << std::endl;

                        }

                    }

                }

            }

        }

    }

    return EXIT_SUCCESS;

}
