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
#include <sstream>
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
    makeGround(650, 900);
    makeDynamicBody(300, 100);
}

SFMLCanvas::~SFMLCanvas()
{
    //Delete anything we "new'd" here:
    delete world;
    delete gravity;
}

/* This code is run when SFMLCanvas::show is called.
 * Creates a render window and starts the timer. */
void SFMLCanvas::showEvent(QShowEvent*)
{
	if (!initialized)
	{
        //Create the actual render window - have to use reinterpret cast since the compiler gets confused using multiple libraries here.
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(this->winId()));
        //Set up textures and such.
		initialize();
        //Allow the user to begin typing immediately, without having to click in the window to begin (focuses the window).
        this->setFocus();
        connect(&repaintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        connect(&gameTimer, SIGNAL(timeout()), this, SLOT(updateGameTime()));
        //Start timer
        repaintTimer.start();
        gameTimer.start(10);
        initialized = true;
        //Start the music
        music.play();
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

/* Initializes all textures and fonts to be used.
 * Most of this code is just reading from files and setting up Text objects. */
void SFMLCanvas::initialize()
{
    if(!pauseTexture.loadFromFile("../MainMenu/Images/pause.png"))
    {
        throw std::invalid_argument("Couldn't find pause image.");
    }
    if(!playTexture.loadFromFile("../MainMenu/Images/play.png"))
    {
        throw std::invalid_argument("Couldn't find play image.");
    }
    if(!backgroundTexture.loadFromFile("../MainMenu/Images/background.png"))
    {
        throw std::invalid_argument("Couldn't find background image.");
    }

    //Some vars used for loading lessons.
    index = 0;
    numMistakes = 0;
    lessonNum = 0;

    textString = "";
    displayString = getNextLesson(lessonNum);

    //Load relevant fonts
    if (!textFont.loadFromFile("../MainMenu/Fonts/GALACTIC_VANGUARDIAN_NCV.ttf"))
    {
        throw std::invalid_argument("Could not find font file.");
    }

    if(!numberFont.loadFromFile(("../MainMenu/Fonts/JLSDataGothicR_NC.otf")))
    {
        throw std::invalid_argument("Couldn't find number font file.");
    }

    //Set up the text for displaying lessons
    initializeText(displayText, 200, 100, displayString.toAnsiString().c_str());

    //Set up string for taking user input
    initializeText(userText, 200, 200, textString.toAnsiString().c_str());

    //Set up text for the timer
    initializeText(timerText, 10, 120, "00:00");
    timerText.setFont(numberFont);
    timerText.setCharacterSize(40);

    //Text to display the number of mistakes made.
    initializeText(mistakeText, 10, 420, "0");
    mistakeText.setCharacterSize(40);
    //Load music files
    if (!music.openFromFile("../MainMenu/Music/Game_Music.ogg"))
    {
        throw std::invalid_argument("Couldn't find game music file.");
    }


}

/* Draws all relevant information to the screen,
 * while "stepping" the Box2D world. */
void SFMLCanvas::update()
{
    //clear the window
    RenderWindow::clear(sf::Color(0, 0, 0));

    //Draw background image
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    draw(background);

    //Draw box2D stuff
    if (state == PLAY)
    {
        world->Step(1/60.f, 8, 3);
    }
    for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
    {
        if (bodyIt->GetType() == b2_dynamicBody)
        {
            sf::Text boxText;
            boxText.setFont(textFont);
            boxText.setString(displayString);
            boxText.setColor(sf::Color(0, 255, 0));
            boxText.setOrigin(16.f, 16.f);
            boxText.setPosition(bodyIt->GetPosition().x * SCALE, bodyIt->GetPosition().y * SCALE);
            boxText.setRotation(bodyIt->GetAngle() * 180/b2_pi);
            boxText.setCharacterSize(FONTSIZE);
            draw(boxText);
        }
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

    //Draw text on top, since it's the most important
    draw(timerText);
    draw(mistakeText);
    draw(displayText);
    draw(userText);

	//Reset clock variable
	clock.restart();
}

/* How Qt intercepts key events.
 * Handles all of the text required interactions. */
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

    //When the game is being played, check for user input.
    if (state == PLAY)
    {
        //When a key is entered...
        if (event->text().at(0).unicode() < static_cast<ushort>(127) && event->text().at(0).unicode() > static_cast<ushort>(31))
        {
            //If the key matches the one in the lesson string move to the next char
            if (event->text().toStdString().at(0) == displayString[index])
            {
                //stringBuild += (static_cast<char>(event.text.unicode));
                textString += event->text().toStdString().at(0);
                index++;
            }
            //If it's not a match add it as a mistake
            else
            {
                numMistakes++;
                std::ostringstream temp;
                temp << numMistakes;
                mistakeText.setString(temp.str());
            }
        }
        //Reaching the end of the line and hitting return will pull the next lesson
        else if (event->key() == Qt::Key_Return)
        {
            if (index == displayString.getSize())
            {
                for (b2Body* bodyIt = world->GetBodyList(); bodyIt != 0; bodyIt = bodyIt->GetNext())
                {
                    if (bodyIt->GetType() == b2_dynamicBody)
                    {
                        world->DestroyBody(bodyIt);
                        makeDynamicBody(userText.getPosition().x, userText.getPosition().y);
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
                displayString = getNextLesson(lessonNum);
                index = 0;
                textString = "";
                userText.setString(textString);
                displayText.setString(displayString);
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

    userText.setString(textString);
    update();
}

/* Creates the ground for Box2D at the given x,y location. */
void SFMLCanvas::makeGround(int x, int y)
{
    //Create ground
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
    bodyDef.type = b2_staticBody;
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(800.f/SCALE, 8.f/SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

/* Creates a dynamic body at the given x,y location.
 * Basic properties are set up, such as density and friction. */
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

/* Sets the game to the paused state, stops the timer (used for WPM). */
void SFMLCanvas::pause()
{
    gameTimer.stop();
    music.pause();
    state = PAUSE;
}

/* Sets the game to the play state, starts the timer (used for WPM). */
void SFMLCanvas::play()
{
    gameTimer.start();
    music.play();
    state = PLAY;
}

/* Initializes the passed in text variable, giving it a font, char size, color, etc.
 * Makes use of the other variables for position and the starting string. */
void SFMLCanvas::initializeText(sf::Text& text, int x, int y, const char* string)
{
    text.setString(string);
    //Default font. Can always be changed outside of the method when needed.
    text.setFont(textFont);
    text.setPosition(x, y);
    //Default color, can also be changed whenever.
    text.setColor(sf::Color(255, 255, 255));
    text.setCharacterSize(FONTSIZE);
}

/* Updates the game timer. This is called roughly every 10 milliseconds, if Qt doesn't mess up.
 * Will also update the timerText's string, so it is ready to draw at all times. */
void SFMLCanvas::updateGameTime()
{
    gameTime += 10;
    //Break game time into hundreth seconds, seconds, and minutes.
    int hs = (gameTime/10)%100;
    int s = (gameTime/1000)%60;
    int m = (gameTime/60000)%60;
    std::ostringstream temp;
    temp << m << ":" << s << ":" << hs;
    //Compose a timer string matching the minute:second:hundredth second format.
    timerText.setString(temp.str());
}
