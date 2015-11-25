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

 

// Here is a small helper for you ! Have a look.

 

int main(int, char const**)

{

    std::cout << "Starting Client" << std::endl;

 

    sf::TcpSocket socket;

    sf::Socket::Status status = socket.connect("localhost", 53000);

    


    sf::Packet outPacket;

    outPacket << "{\"action\":5,\"user\":\"tpope\",\"password\":\"pass123\"}";

    socket.send(outPacket);

	sf::Packet data;

	if (socket.receive(data) != sf::Socket::Done)
	{
	    // error...
	}
	// std::cout << "Received " << received << " bytes" << std::endl;
	std::string msg;

    data >> msg;

    std::cout << "Msg received: " << msg << std::endl;

    
    data >> msg;

    std::cout << "Msg received: " << msg << std::endl;


    socket.disconnect();

    return EXIT_SUCCESS;

}