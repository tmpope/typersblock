#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main(int, char const**)
{
    sf::TcpSocket socket;
    sf::Packet outPacket;
    sf::Packet data;

    sf::Socket::Status status = socket.connect("localhost", 53000);
    outPacket << "{\"action\":0,\"user\":\"tpope\",\"password\":\"pass123\"}";
    // outPacket << "{\"action\":0,\"user\":\"tpope\",\"password\":\"wrongPass\"}";
    // outPacket << "{\"action\":1,\"user\":\"tpope\",\"password\":\"pass123\"}";
    // outPacket << "{\"action\":2,\"user\":\"tpope\",\"password\":\"pass123\"}";
    socket.send(outPacket);
	if (socket.receive(data) != sf::Socket::Done)
	{
	   std::cout << "Error" << std::endl;
	}
	std::string msg;
    data >> msg;
    std::cout << "Msg received: " << msg << std::endl;
    socket.disconnect();

    return EXIT_SUCCESS;
}