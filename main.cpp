//Typer's Block - Sprint One
//Client - Server interaction base code
//Recommended to use ctrl+F5 (if in visual studio) to run this, so that the console window stays open after everything has finished running and printing to the console.

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "simpleJSON/JSON.h"
#include "simpleJSON/JSONValue.h"
#include <iostream>


//Will wait for a response from the server
//TODO: Do something useful with the response, aside from printing to the console (Sprint 2)
static std::string listenForResponse(sf::TcpSocket& socket)
{
	//Variables to store information for the response from the server
	char buffer[512];
	sf::IpAddress responseIp;
	size_t responseSize;

	//This is a blocking operation!
	socket.receive(buffer, 512, responseSize);
	socket.disconnect();

	//Turn the response into a string
	std::string response(buffer, responseSize);
	std::cout << response << std::endl;

	return response;
}

//Sends a packet to the server, using the given data. 
//The data should have been encoded in JSON before being sent.
static void sendPacket(std::string dataString)
{
	std::cout << dataString << std::endl;
	//Set up ip socket and packet
	sf::IpAddress ip("127.0.0.1");
	sf::TcpSocket socket;
	sf::Packet packet;
	//Connect to the server
	sf::Socket::Status status = socket.connect(ip, 53000);

	//Attach our information to the packet
	packet.append(dataString.c_str(), dataString.length());
	//Send the packet
	if (socket.send(packet) != sf::Socket::Done)
	{
		std::cout << "Error occurred while sending a packet." << std::endl;
	}
	else
	{
		std::cout << "Packet sent successfully." << std::endl;
	}
	listenForResponse(socket);
}

//Given a JSONObject, takes care of Stringify and conversion from a wstring to a string
static std::string convertJSONtoString(JSONObject data)
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

//Try to login to the server with the given credentials.
//TODO: Salt the password! (During Sprint 2)
static void loginRequest()
{
	//Temporary code to allow the user to input a username and password
	std::wstring username, password;
	std::cout << "Username: " << std::endl;
	std::wcin >> username;
	std::cout << "Password: " << std::endl;
	std::wcin >> password;

	//Going to store all our JSON information in here.
	JSONObject data;
	data[L"action"] = new JSONValue(L"0");
	data[L"username"] = new JSONValue(username);
	data[L"password"] = new JSONValue(password);

	//Convert and send the packet
	sendPacket(convertJSONtoString(data));
}

//Tell the server to create a user with the given information.
static void creationRequest()
{
	//Temporary code to allow the user to input a username and password
	std::wstring username, password, firstName, lastName, className;
	std::cout << "Username: " << std::endl;
	std::wcin >> username;
	std::cout << "Password: " << std::endl;
	std::wcin >> password;
	std::cout << "First Name: " << std::endl;
	std::wcin >> firstName;
	std::cout << "Last Name: " << std::endl;
	std::wcin >> lastName;
	std::cout << "Class: " << std::endl;
	std::wcin >> className;

	//Going to store all our JSON information in here.
	JSONObject data;

	data[L"action"] = new JSONValue(L"1");
	data[L"username"] = new JSONValue(username);
	data[L"password"] = new JSONValue(password);
	data[L"firstname"] = new JSONValue(firstName);
	data[L"lastname"] = new JSONValue(lastName);
	data[L"class"] = new JSONValue(className);

	//Convert and send the packet
	sendPacket(convertJSONtoString(data));
}

//Tells the server what keyboard is currently being used, and which keyboard we are to emulate.
//After this information is given to the server, the corresponding set of key mappings will be returned to the client.
//TODO: Figure out how the information is being sent back from the server, and pull it out of the JSON.
static void getKeyMappings()
{
	std::wstring actualKeyboard, virtualKeyboard;

	std::cout << "Actual keyboard configuration: (i.e. qwerty, dvorak, azerty)" << std::endl;
	std::wcin >> actualKeyboard;
	std::cout << "Desired virtual keyboard configuration: " << std::endl;
	std::wcin >> virtualKeyboard;

	JSONObject data;

	data[L"action"] = new JSONValue(L"2");
	data[L"actualkeyboard"] = new JSONValue(actualKeyboard);
	data[L"virtualkeyboard"] = new JSONValue(virtualKeyboard);

	//Convert and send the packet
	sendPacket(convertJSONtoString(data));
}


int main()
{
	while (true)
	{
		//Ask if they want to login, or make a new user.
		std::cout << "To login, enter 'login'. To create a new user, enter 'create'. To get kepmappings from your physical keyboard to a virtual keyboard, enter 'keymap'." << std::endl;
		std::string mode;
		std::cin >> mode;
		if (mode == "login")
		{
			//Go to login dialog
			loginRequest();
			break;
		}
		else if (mode == "create")
		{
			//Go to user creation dialog
			creationRequest();
			break;
		}
		else if (mode == "keymap")
		{
			//Go to keymappings
			getKeyMappings();
			break;
		}
		else
		{
			std::cout << "Invalid input. Must enter 'login', 'create', or 'keymap' to continue. Please try again." << std::endl;
		}
	}

	return 0;
}