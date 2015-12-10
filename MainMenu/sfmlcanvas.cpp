#define _USE_MATH_DEFINES
#define SCALE 30
#define FONTSIZE 26
#define START 1
#define PLAY 2
#define PAUSE 3
#define END 4

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
#include <math.h>

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
    makeDynamicBody(300, 100);

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
    //Load relevant textures.
    if(!ground.loadFromFile("../MainMenu/Images/ground.png"))
    {
        qDebug() << "Couldn't find ground texture file.";
    }
    if(!pauseTexture.loadFromFile("../MainMenu/Images/pause.png"))
    {
        qDebug() << "Couldn't find pause texture file.";
    }
    if(!playTexture.loadFromFile("../MainMenu/Images/play.png"))
    {
        qDebug() << "Couldn't find play texture file.";
    }
    if(!backgroundTexture.loadFromFile("../MainMenu/Images/background.png"))
    {
        qDebug() << "Couldn't find background texture file.";
    }

    index = 0;
    numMistakes = 0;
    lessonNum = 0;

    TextString = "";
    DisplayString = getNextLesson(lessonNum);
    if (!Font.loadFromFile("../MainMenu/Fonts/GALACTIC_VANGUARDIAN_NCV.ttf"))
    {
        throw std::invalid_argument("Could not find font file");
    }

    //Set up the text for displaying lessons
    displayText.setString(DisplayString);
    displayText.setFont(Font);
    displayText.setPosition(200, 200);
    displayText.setColor(sf::Color(255, 255, 255));
    displayText.setCharacterSize(FONTSIZE);

    //Set up string for taking user input
    text.setString(TextString);
    text.setFont(Font);
    text.setPosition(200, 300);
    text.setColor(sf::Color(255, 255, 255));
    text.setCharacterSize(FONTSIZE);
}

void SFMLCanvas::update()
{
    //clear the window
    RenderWindow::clear(sf::Color(0, 0, 0));

    //Draw background image
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    draw(background);

    //Draw box2D stuff
    world->Step(1/60.f, 8, 3);
    for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
    {
        if (bodyIt->GetType() == b2_dynamicBody)
        {
            sf::Text boxText;
            boxText.setFont(Font);
            boxText.setString(DisplayString);
            boxText.setColor(sf::Color(0, 255, 0));
            boxText.setOrigin(16.f, 16.f);
            boxText.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            boxText.setRotation(bodyIt->GetAngle() * 180/b2_pi);
            boxText.setCharacterSize(FONTSIZE);
            draw(boxText);
        }
        /*else
        {
            sf::Sprite groundSprite;
            groundSprite.setTexture(ground);
            groundSprite.setOrigin(400.f, 8.f);
            groundSprite.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            groundSprite.setRotation(180/b2_pi * bodyIt->GetAngle());
            RenderWindow::draw(groundSprite);
        }*/
    }

    //Draw pause icon when paused
    if (state == PAUSE)
    {
        sf::Sprite pauseSprite;
        pauseSprite.setTexture(pauseTexture);
        //Dynamically position the pause texture in the middle of the screen.
        pauseSprite.setPosition(((this->size().rwidth()/2) - pauseTexture.getSize().x/2), ((this->size().rheight()/2) - pauseTexture.getSize().y/2));
        draw(pauseSprite);
    }
    //Draw play icon while playing
    else if (state == PLAY)
    {
        sf::Sprite playSprite;
        playSprite.setTexture(playTexture);
        playSprite.setPosition(10, (this->size().rheight() - playTexture.getSize().x) - 10);
        draw(playSprite);
    }

    //Draw typing text on top, since it's the most important
    draw(displayText);
    draw(text);

	//Reset clock variable
	clock.restart();
}

void SFMLCanvas::keyPressEvent(QKeyEvent* event)
{
    //Pause or unpause when escape is pressed.
    if (event->key() == Qt::Key_Escape)
    {
        switch(state)
        {
        case START:
            //begin
            break;
        case PLAY:
            pause();
            break;
        case PAUSE:
            play();
            break;
        case END:
            //finish game
            break;
        }
    }

    if (state == PLAY)
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
            if (index == DisplayString.getSize())
            {
                for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
                {
                    if (bodyIt->GetType() == b2_dynamicBody)
                    {
                        world->DestroyBody(bodyIt);
                        makeDynamicBody(text.getPosition().x, text.getPosition().y);
                    }
                }
                for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
                {
                    if (bodyIt->GetType() == b2_dynamicBody)
                    {
                        bodyIt->SetFixedRotation(false);
                        //Apply torque in a random angle from -45 degrees to 45 degrees
                        srand(time(NULL));
                        int temp = rand() % 137 + (-68);
                        double angle = temp*M_PI/180;
                        bodyIt->ApplyAngularImpulse(angle, true);
                        //Give it a little upward push - not sure this does anything
                        //bodyIt->ApplyLinearImpulse(b2Vec2(0, 10), bodyIt->GetWorldCenter(), true);
                    }
                }
                lessonNum++;
                DisplayString = getNextLesson(lessonNum);
                index = 0;
                TextString = "";
                text.setString(TextString);
                displayText.setString(DisplayString);
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

    text.setString(TextString);
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

void SFMLCanvas::makeDynamicBody(int x, int y)
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
    std::ifstream myfile("../MainMenu/Lessons/lesson.txt");
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
    state = PAUSE;
}

void SFMLCanvas::play()
{
    gameTimer.start();
    state = PLAY;
}
