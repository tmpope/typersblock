#include <SFML/Network.hpp>

#include <iostream>

#include <vector>
#include <string>
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

sql::ResultSet* runSqlQuery(std::string query)
{
    sql::ResultSet *res;
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    try 
    {
        driver = get_driver_instance();
        con = driver->connect("waihoilaf.duckdns.org", "typerblock", "TyPeRbL0(k");
        stmt = con->createStatement();
        stmt->execute("USE TyperBlock");
        res = stmt->executeQuery(query.c_str());
        delete stmt;
        delete con;
        return res;
    } 
    catch (sql::SQLException &e) {
        if(e.getErrorCode() == 0)
        {
            delete stmt;
            delete con;
            return res;
        }
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "
            << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        if(stmt)
        {
            delete stmt;
        }
        if(con)
        {
            delete con;
        }
        return res;
    }
}
int insertNewUser(std::string user, std::string pass, std::string first, std::string last, std::string className)
{
    sql::ResultSet *res;
    std::string query = "INSERT INTO user_table values('" + user
        + "', 'doesnt', '" + pass + "', '" + className + "', 0, now(), now(), '" 
        + first + "', '" + last + "')";
    std::cout << query << std::endl;
    runSqlQuery(query);
    return 0;
}


bool validate(std::string user, std::string pass) 
{
    bool result = false;
    std::string query = "SELECT first_name FROM user_table where username = '" + user
        + "' AND password = '" + pass + "'";
    sql::ResultSet *res = runSqlQuery(query);
    while (res->next()) {
        result = true;
    }
    return result;
}

int* getScores(std::string user, int& scoreCount) 
{
    std::string query = "SELECT score FROM scores_table WHERE user='" + user + "'";

    sql::ResultSet *res = runSqlQuery(query);
    scoreCount = res->rowsCount();
    int* scores = new int[scoreCount];
    for (int i = 0; i < scoreCount; i++)
    {
        scores[i] = 0;
    }
    int counter = 0;
    while (res->next())
    {
        int score = res->getInt(1);
        std::cout << "Got a score: " << score << std::endl;
        scores[counter++] = score;
    }

  return scores;
}

void insertScore(std::string user, std::string pass, int level, int wpm, int mistakes, int score) {
    sql::ResultSet *res;
    std::string query = "INSERT INTO scores_table values('" + user
        + "', " + std::to_string(level) + ", " + std::to_string(wpm) + ", " 
        + std::to_string(mistakes) + ", " + std::to_string(score) + ")"
        + " ON DUPLICATE KEY UPDATE score = " + std::to_string(score);
    std::cout << query << std::endl;
    runSqlQuery(query);
    return;
}

/**
 * Error
 * @param  user [description]
 * @param  pass [description]
 * @return      [description]
 */
std::string generateResponse(std::string error)
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
    writer.String("type");
    writer.String("error");
    writer.String("message");
    writer.String(error.c_str());
    writer.EndObject();
    return s.GetString();
}

/**
 * Login
 * @param  user [description]
 * @param  pass [description]
 * @return      [description]
 */
std::string generateResponse(std::string user, std::string pass)
{
  // TODO: Ensure that we get all of this figured out
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

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

	int scoreCount;
    int* scores = getScores(user, scoreCount);
        for (int i = 0; i < scoreCount; i++)
            writer.Uint(scores[i]);

        writer.EndArray();
        writer.EndObject();
        return s.GetString();//"Valid login for user " + user;
    }
    else
    {
        writer.StartObject();
        writer.String("type");
        writer.String("failure");
        writer.String("message");
        writer.String("Invalid username password combination");
        writer.EndObject();
        return s.GetString();//"Valid login for user " + user;
    }
    return s.GetString();
}

/**
 * Create user
 * @param  user      [description]
 * @param  pass      [description]
 * @param  first     [description]
 * @param  last      [description]
 * @param  className [description]
 * @return           [description]
 */
std::string generateResponse(std::string user, std::string pass, std::string first, std::string last, std::string className)
{
    insertNewUser(user, pass, first, last, className);
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
    if (validate(user, pass))
    {
        writer.StartObject();
        writer.String("type");
        writer.String("success");
        writer.String("user");
        writer.String(user.c_str());
        writer.String("class");
        writer.String(className.c_str());
        writer.EndObject();
        return s.GetString();//"Valid login for user " + user;
    }
    else
    {
        return "Invalid username password combination";
    }
    return s.GetString();
}

/**
 * Update score
 * @param  user      [description]
 * @param  pass      [description]
 * @param  first     [description]
 * @param  last      [description]
 * @param  className [description]
 * @return           [description]
 */
std::string generateResponse(std::string user, std::string pass, int level, int wpm, int mistakes, int score)
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
    if (validate(user, pass))
    {
        insertScore(user, pass, level, wpm, mistakes, score);
        //return login result
        writer.StartObject();
        writer.String("type");
        writer.String("success");
        writer.String("user");
        writer.String(user.c_str());
        writer.EndObject();
        return s.GetString();
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
    sf::Packet packet;
    if (document.Parse(msg.c_str()).HasParseError() || !document.HasMember("action"))
    {
        packet << generateResponse("Invalid JSON");
        if (client->send(packet) != sf::Socket::Done)
        {
            std::cout << "Error occurred while sending a packet." << std::endl;
        }
        return;
    }
    int action = document["action"].GetInt();
    std::string user, pass, first, last, className;
    int level, wpm, mistakes, score;
    std::cout << "action : " << action << std::endl;
    switch(action){
        case 0  : //login
            if (!document.HasMember("user") || !document.HasMember("password"))
            {
                packet << generateResponse("Invalid JSON for login");
                if (client->send(packet) != sf::Socket::Done)
                {
                    std::cout << "Error occurred while sending a packet." << std::endl;
                }
                return;
            }
            user = document["user"].GetString();
            pass = document["password"].GetString();
            std::cout << "user : " << user << std::endl;
            packet << generateResponse(user, pass);
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            return;
        case 1  : //create user
            if (!document.HasMember("user") || !document.HasMember("password")
                 || !document.HasMember("first")  || !document.HasMember("last")
                  || !document.HasMember("className"))
            {
                packet << generateResponse("Invalid JSON for user creation");
                if (client->send(packet) != sf::Socket::Done)
                {
                    std::cout << "Error occurred while sending a packet." << std::endl;
                }
                return;
            }
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
            return;
        case 2  : //get key mapping
            std::cout << "Keymapping" << std::endl;
            return;
        case 3  : //set score
            if (!document.HasMember("user") || !document.HasMember("password")
                 || !document.HasMember("level") || !document.HasMember("wpm") 
                 || !document.HasMember("mistakes") || !document.HasMember("score"))
            {
                packet << generateResponse("Invalid JSON for score update");
                if (client->send(packet) != sf::Socket::Done)
                {
                    std::cout << "Error occurred while sending a packet." << std::endl;
                }
                return;
            }
            user = document["user"].GetString();
            pass = document["password"].GetString();
            level = document["level"].GetInt();
            wpm = document["wpm"].GetInt();
            mistakes = document["mistakes"].GetInt();
            score = document["score"].GetInt();
            std::cout << "user : " << user << std::endl;
            packet << generateResponse(user, pass, level, wpm, mistakes, score);
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            return;
        default : //any other action
            packet << "Invalid Action";
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Error occurred while sending a packet." << std::endl;
            }
            return;
    }
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
