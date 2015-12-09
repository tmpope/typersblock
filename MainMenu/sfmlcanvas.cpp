#include "sfmlcanvas.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "qdebug.h"
#include "Box2D/Box2D.h"
#include "iostream"
#include <QKeyEvent>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <iostream>
#define SCALE 30
SFMLCanvas::SFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, int frameTime) : QWidget(parent), initialized(false)
{
	//Allow rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	//Enable keyboard events
	setFocusPolicy(Qt::StrongFocus);
	//Location and size
	move(position);
	resize(size);
	//Set timer interval
	timer.setInterval(frameTime);
    this->setFramerateLimit(60);
    //Set up some basic Box2D stuff
    gravity = new b2Vec2(0.0f, -10.0f);
    world = new b2World(*gravity);
    makeGround(300, 300);
    makeBox(300, 500);
}

SFMLCanvas::~SFMLCanvas()
{

}

void SFMLCanvas::showEvent(QShowEvent*)
{
	if (!initialized)
	{
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(this->winId()));
		initialize();
        qDebug() << "Window initialized.";
		connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
		timer.start();
		initialized = true;
	}
}

QPaintEngine* SFMLCanvas::paintEngine() const
{
	return 0;
}

void SFMLCanvas::paintEvent(QPaintEvent*)
{
	update();
	RenderWindow::display();
}

void SFMLCanvas::initialize()
{
    /*if (!texture.loadFromFile("../MainMenu/linkTexture.jpg"))
	{
        qDebug() << "Couldn't find file at \"C:/Users/ryant_000/Downloads/typersblock/MainMenu/linkTexture.jpg\"";
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setPosition(50, 50);
		clock.restart();
    }*/


    if (!ground.loadFromFile("../MainMenu/ground.png"))
    {
        qDebug() << "Couldn't find ground texture file.";
    }
    if (!box.loadFromFile("../MainMenu/box.png"))
    {
        qDebug () << "Couldn't find box texture file.";
    }

    index = 0;
    numMistakes = 0;
    lessonNum = 0;

    TextString = "";
    DisplayString = getNextLesson(lessonNum);
    if (!Font.loadFromFile("../MainMenu/arial.ttf"))
    {
        throw std::invalid_argument("Could not find font file");
    }

    //Set up the text for displaying lessons
    DisplayText.setString(DisplayString);
    DisplayText.setFont(Font);
    DisplayText.setPosition(0, 0);
    DisplayText.setColor(sf::Color(255, 255, 255));
    DisplayText.setCharacterSize(24);

    //Set up string for taking user input
    Text.setString(TextString);
    Text.setFont(Font);
    Text.setPosition(0, 40);
    Text.setColor(sf::Color(255, 255, 255));
    Text.setCharacterSize(24);
}

void SFMLCanvas::update()
{

    //clear the window
    RenderWindow::clear(sf::Color(0, 0, 0));
    //Draw box2D stuff
    world->Step(1/60.f, 8, 3);
    for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
    {
        if (bodyIt->GetType() == b2_dynamicBody)
        {
            sf::Sprite boxSprite;
            boxSprite.setTexture(box);
            boxSprite.setOrigin(16.f, 16.f);
            boxSprite.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            boxSprite.setRotation(bodyIt->GetAngle() * 180/b2_pi);
            RenderWindow::draw(boxSprite);
        }
        else
        {
            sf::Sprite groundSprite;
            groundSprite.setTexture(ground);
            groundSprite.setOrigin(400.f, 8.f);
            groundSprite.setPosition(bodyIt->GetPosition().x * 30, bodyIt->GetPosition().y * 30);
            groundSprite.setRotation(180/b2_pi * bodyIt->GetAngle());
            RenderWindow::draw(groundSprite);
        }
    }
	//Rotate 100 degrees per second
    //sprite.rotate(clock.getElapsedTime().asSeconds() * 100.f);
	//Draw the sprite
    //RenderWindow::draw(sprite);

    RenderWindow::draw(DisplayText);
    RenderWindow::draw(Text);

	//Reset clock variable
	clock.restart();
}

void SFMLCanvas::keyPressEvent(QKeyEvent* event)
{
    //Exit the program when escape is pressed
    if (event->key() == Qt::Key_Escape)
    {
        this->QWidget::close();
    }
    //std::cout << event.text.unicode << std::endl;

    //If the key entered
    if (event->text().at(0).unicode() < static_cast<ushort>(127) && event->text().at(0).unicode() > static_cast<ushort>(31))
    {
        //If the key matches the one in the lesson string move to the next char
        if (event->text().toStdString().at(0) == DisplayString[index])
        {
            //stringBuild += (static_cast<char>(event.text.unicode));
            TextString += event->text().toStdString().at(0);
            index++;
        }
        //If it's not a match add it as a mistake
        else
        {
            numMistakes++;
            std::cout << "You made " << numMistakes << " mistakes" << std::endl;
        }
    }
    //Reaching the end of the line and hitting return will pull the next lesson
    else if (event->key() == Qt::Key_Return)
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
    //Implementation of previous function using unicode
    /*else if (event->text().at(0).unicode() == static_cast<ushort>(13))
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
    //implementation of backspace if we ever need it
    else if (event->key() == Qt::Key_Backspace)
    {
        //stringBuild = stringBuild.substr(0, stringBuild.size() - 1);
        TextString = TextString.substring(0, TextString.getSize() - 1);
        index--;
    }*/
    //std::cout << "Your string is :" << stringBuild << std::endl;

    Text.setString(TextString);
    update();

    //qDebug() << event->text().at(0).unicode();
}

void SFMLCanvas::makeGround(int x, int y)
{
    //Create ground
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
    bodyDef.type = b2_staticBody;
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(400.f/SCALE, 8.f/SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

void SFMLCanvas::makeBox(int x, int y)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(32.f/SCALE, 32.f/SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = .7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

sf::String SFMLCanvas::getNextLesson(int indexOfLesson)
{
    std::string line;
    std::ifstream myfile("../MainMenu/lesson.txt");
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
    return "";
}
