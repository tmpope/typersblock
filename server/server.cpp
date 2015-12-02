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

bool validate(std::string user, std::string pass) 
{
    return user == "tpope" && pass == "pass123";
}

int getScore(std::string user, int level) 
{
    return 3;
}

bool createUser(std::string user, std::string pass, std::string first, std::string last, std::string className) 
{
    return false;
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
            break;
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
            break;
        case 2  : //get key mapping
            std::cout << "Keymapping" << std::endl;
            break;
        default : //any other action
            packet << "Invalid Action";
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            break;
    }
}

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
        std::cout << "Connection Error" << std::endl;
    }


    std::vector<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    selector.add(listener);

    while (1)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);
                    selector.add(*client);
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it; // reference to the actual socket 1st * for it dereference second for pointer
                    if (selector.isReady(client))
                    {
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
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
