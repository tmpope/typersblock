//Some brief test code that prints out to the console what the user types on the keyboard.
//I'm keeping this file commented as of now, so that it doesn't interfere with us running the other main method.
//To test this, comment out the main.cpp and uncomment this. I know it's a bandaid fix, but this is simply for testing and won't be used as part of the final product.

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
/*
int main()
{
	//Some base code found in the SFML setup tutorial.Can be used to test if the entire SFML library is working.
	//This is all test code that happens to be in this same project. It can be commented out, and will be removed and placed elsewhere once integrated into the project as a whole.
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	//Window will no longer allow multiple key pressed events to trigger from holding down one key.
	window.setKeyRepeatEnabled(false);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::TextEntered)
			{
				//Print out the text that was typed to the console.
				if (event.text.unicode < 128)
				{
					std::cout << static_cast<char>(event.text.unicode);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					//Enter a new line.
					std::cout << std::endl;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					//Exit the program.
					return 0;
				}
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}*/