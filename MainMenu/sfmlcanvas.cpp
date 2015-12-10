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
    //Allows us to return to the previous screen
    prev = parent;

	//Allow rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

    //Enable keyboard events
	setFocusPolicy(Qt::StrongFocus);

    //Set location and size of the canvas
	move(position);
	resize(size);

	//Set timer interval
    repaintTimer.setInterval(frameTime);
    this->setFramerateLimit(60);

    //Set up some basic Box2D stuff
    gravity = new b2Vec2(1.0f, 10.0f);
    world = new b2World(*gravity);
    makeGround(300, 700);
    makeBox(300, 100);

    //Set quit button properties
    quitButton.adjustSize();

}

SFMLCanvas::~SFMLCanvas()
{

}

/* This code is run when SFMLCanvas::show is called.
 * Creates a render window and starts the timer. */
void SFMLCanvas::showEvent(QShowEvent*)
{
	if (!initialized)
	{
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(this->winId()));
        //Set up textures and such.
		initialize();
        //Allow the user to begin typing immediately, without having to click in the window to begin.
        this->setFocus();

        connect(&repaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));

        repaintTimer.start();
        gameTimer.start();
        initialized = true;
	}
}

QPaintEngine* SFMLCanvas::paintEngine() const
{
	return 0;
}

/* Called everytime the Qt window redraws. Simply invokes the update method in turn. */
void SFMLCanvas::paintEvent(QPaintEvent*)
{
	update();
	RenderWindow::display();
}

void SFMLCanvas::initialize()
{
    if(!ground.loadFromFile("../MainMenu/ground.png"))
    {
        qDebug() << "Couldn't find ground texture file.";
    }
    if(!box.loadFromFile("../MainMenu/box.png"))
    {
        qDebug() << "Couldn't find box texture file.";
    }

    if(!pauseTexture.loadFromFile("../MainMenu/pause.png"))
    {
        qDebug() << "Couldn't find pause texture file.";
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
    DisplayText.setPosition(200, 200);
    DisplayText.setColor(sf::Color(255, 255, 255));
    DisplayText.setCharacterSize(36);

    //Set up string for taking user input
    Text.setString(TextString);
    Text.setFont(Font);
    Text.setPosition(200, 300);
    Text.setColor(sf::Color(255, 255, 255));
    Text.setCharacterSize(36);
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
            /*sf::Sprite boxSprite;
            boxSprite.setTexture(box);
            boxSprite.setOrigin(16.f, 16.f);
            boxSprite.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            boxSprite.setRotation(bodyIt->GetAngle() * 180/b2_pi);*/
            sf::Text boxText;
            boxText.setFont(Font);
            boxText.setString(DisplayString);
            boxText.setColor(sf::Color(0, 255, 0));
            boxText.setOrigin(16.f, 16.f);
            boxText.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            boxText.setRotation(bodyIt->GetAngle() * 180/b2_pi);
            boxText.setCharacterSize(36);
            RenderWindow::draw(boxText);
        }
        else
        {
            sf::Sprite groundSprite;
            groundSprite.setTexture(ground);
            groundSprite.setOrigin(400.f, 8.f);
            groundSprite.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            groundSprite.setRotation(180/b2_pi * bodyIt->GetAngle());
            RenderWindow::draw(groundSprite);
        }
    }
    //Draw pause icon when paused
    if (paused)
    {
        sf::Sprite pauseSprite;
        pauseSprite.setTexture(pauseTexture);
        pauseSprite.setPosition(583, 309);
        draw(pauseSprite);
    }
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
        paused = !paused;
        if (paused)
        {
            pause();
        }
        else
        {
            play();
        }
    }

    if (!paused)
    {
        //When a key is entered...
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
                for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
                {
                    if (bodyIt->GetType() == b2_dynamicBody)
                    {
                        world->DestroyBody(bodyIt);
                        makeBox(200, 300);
                        qDebug() << "How many in world body list " << world->GetBodyCount();
                    }
                }
                lessonNum++;
                DisplayString = getNextLesson(lessonNum);
                index = 0;
                TextString = "";
                Text.setString(TextString);
                DisplayText.setString(DisplayString);

            }
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

    Text.setString(TextString);
    update();
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
        {
            if (lineno == indexOfLesson)
            {
                return line;
            }
        }
        myfile.close();
    }

    else std::cout << "Unable to open file";
    return "";
}

void SFMLCanvas::pause()
{
    gameTimer.stop();
}

void SFMLCanvas::play()
{
    gameTimer.start();
}
