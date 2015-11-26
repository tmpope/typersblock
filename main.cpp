#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\String.hpp>
#include <SFML\Graphics\Font.hpp>
#include <iostream>
#include <string.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Typing editor");

	// Create a graphical text to display
	std::string stringBuild("");
	sf::String TextString("");
	sf::Font Font;
	if (!Font.loadFromFile("arial.ttf"))
	{
		return 1;
	}
	sf::Text Text;
	Text.setString(TextString);
	Text.setFont(Font);
	Text.setColor(sf::Color(255, 255, 255));
	Text.setCharacterSize(24);

	while (window.isOpen())
	{
		sf::Event event;
		//This portion of code allows the user to any key beside special characters
		//Also implemented backspace
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				//std::cout << event.text.unicode << std::endl;
				if ((event.text.unicode < 127 && event.text.unicode > 31))
				{
					//stringBuild += (static_cast<char>(event.text.unicode));
					TextString += (static_cast<char>(event.text.unicode));
				}
				else if (event.text.unicode == 8)
				{
					//stringBuild = stringBuild.substr(0, stringBuild.size() - 1);
					TextString = TextString.substring(0, TextString.getSize() - 1);
				}
				else if (event.text.unicode == 13)
				{
					TextString += "\n";
				}
				//std::cout << "Your string is :" << stringBuild << std::endl;

				Text.setString(TextString);
			}
		}
		window.clear();
		window.draw(Text);
		window.display();
	}
	return 0;
}
//What ever the map needs to be 
//std::map<char, char> keyMap();

/*public char matchKey(char c)
{
	if (keyMap.find(c) != keyMap.end())
		return keyMap[c];
	else 
		return "\0";
}*/