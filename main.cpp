#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\String.hpp>
#include <SFML\Graphics\Font.hpp>
#include <iostream>
#include <string.h>
#include <fstream>


sf::String getNextLesson(int indexOfLesson)
{
	std::string line;
	std::ifstream myfile("lesson.txt");
	if (myfile.is_open())
	{
		for (int lineno = 0; getline(myfile, line) && lineno < 1000; lineno++)
			if (lineno == indexOfLesson)
			{
				return line;
			}
		myfile.close();
	}

	else std::cout << "Unable to open file";

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Typing editor");

	// Create a graphical text to display
	//std::string stringBuild("");

	int numMistakes = 0;
	int lessonNum = 0;

	sf::String TextString("");
	//sf::String DisplayString("This is sample text to make sure we can make a lesson");
	sf::String DisplayString = getNextLesson(lessonNum);
	sf::Font Font;
	if (!Font.loadFromFile("arial.ttf"))
	{
		return 1;
	}

	sf::Text DisplayText;
	DisplayText.setString(DisplayString);
	DisplayText.setFont(Font);
	DisplayText.setPosition(0, 0);
	DisplayText.setColor(sf::Color(0, 0, 0));
	DisplayText.setCharacterSize(24);

	sf::Text Text;
	Text.setString(TextString);
	Text.setFont(Font);
	Text.setPosition(0, 40);
	Text.setColor(sf::Color(0, 0, 0));
	Text.setCharacterSize(24);

	size_t index = 0;

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
					if (static_cast<char>(event.text.unicode) == DisplayString[index])
					{
						//stringBuild += (static_cast<char>(event.text.unicode));
						TextString += (static_cast<char>(event.text.unicode));
						index++;
					}
					else
					{
						numMistakes++;
						std::cout << "You made " << numMistakes << " mistakes" << std::endl;	
					}
				}
				/*else if (event.text.unicode == 8)
				{
					//stringBuild = stringBuild.substr(0, stringBuild.size() - 1);
					TextString = TextString.substring(0, TextString.getSize() - 1);
				}*/
				else if (event.text.unicode == 13)
				{
					//TextString += "\n";
					if (index == DisplayString.getSize())
					{
						lessonNum++;
						DisplayString = getNextLesson(lessonNum);
						index = 0;
						TextString = "";
						Text.setString(TextString);
						DisplayText.setString(DisplayString);
					}
					
				}
				//std::cout << "Your string is :" << stringBuild << std::endl;
				
				Text.setString(TextString);
			}
		}
		window.clear(sf::Color(255, 255, 255));
		window.draw(DisplayText);
		window.draw(Text);
		window.display();
	}
	return 0;
}
//What ever the map needs to be 
//std::map<char, char> keyMap();

/*public char matchKey(char c, map<char, char> keyMapping)
{
	//Search the map for the char mapping and return it if it is found
	if (keyMap.find(c) != keyMapping.end())
		return keyMapping[c];
	//return a null character if the character can not be mapped
	else 
		return "\0";
}*/

sf::String buildString(sf::String selectionOfChars)
{
	int numberOfWords = rand() % 2 + 7;
	sf::String builtString("");
	for (int i = 0; i < numberOfWords; i++)
	{
		int sizeOfWord = rand() % 4 + 2;
		for (int i = 0; i < sizeOfWord; i++)
		{
			builtString += selectionOfChars[rand() % selectionOfChars.getSize()];
		}
		builtString += " ";
	}
	return builtString.substring(0, builtString.getSize() - 1);
}
