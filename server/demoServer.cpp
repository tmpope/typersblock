//

// Disclamer:

// ----------

//

// This code will work only if you selected window, graphics and audio.

//

// Note that the "Run Script" build phase will copy the required frameworks

// or dylibs to your application bundle so you can execute it on any OS X

// computer.

//

// Your resource files (images, sounds, fonts, ...) are also copied to your

// application bundle. To get the path to these resource, use the helper

// method resourcePath() from ResourcePath.hpp

//

 

#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>

#include <SFML/Network.hpp>

#include <iostream>

#include <vector>


#include "reader.h"
#include "document.h"
#include <iostream>

// using namespace rapidjson;
// using namespace std;

void process(std::string msg, sf::TcpSocket* socket) {
    std::cout << "Processing..." << std::endl;
    rapidjson::Document document;
    if (document.Parse(msg.c_str()).HasParseError())
    {
        std::cout << "JSON ERROR" << std::endl;
        return;
    }
    int action = document["action"].GetInt();
    std::string user = document["user"].GetString();
    std::string pass = document["password"].GetString();
    std::cout << "action : " << action << std::endl;
    sf::Packet packet;
    switch(action){
        case 0  : //login
            std::cout << "user : " << user << std::endl;
            // packet << "test string";
            // if (socket->send(packet) != sf::Socket::Done)
            // {
            //     std::cout << "Error occurred while sending a packet." << std::endl;
            // }
            break; //optional
        case 1  : //create user
            std::cout << "user : " << user << std::endl;
            std::cout << "pass : " << pass << std::endl;
            break; //optional
        case 2  : //get key mapping
            std::cout << "Keymapping" << std::endl;
            break;
      
        // you can have any number of case statements.
        default : //Optional
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
                            // sf::Packet packet2;
                            // packet2 << "{\"action\":" << 13 << ",\"user\":\"tpope\"}";
                            // client.send(packet2);

                            std::cout << "Msg received: " << msg << std::endl;

                        }

                    }

                }

            }

        }

    }

    return EXIT_SUCCESS;

}
