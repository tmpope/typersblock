#include "sfmlcanvas.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "qdebug.h"
#include "Box2D/Box2D.h"
#include "iostream"
#include <QKeyEvent>
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
    if (!texture.loadFromFile("C:/Users/ryant_000/Downloads/typersblock/MainMenu/linkTexture.jpg"))
	{
        qDebug() << "Couldn't find file at \"C:/Users/ryant_000/Downloads/typersblock/MainMenu/linkTexture.jpg\"";
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setPosition(50, 50);
		clock.restart();
	}
    if (!ground.loadFromFile("C:/Users/ryant_000/Downloads/typersblock/MainMenu/ground.png"))
    {
        qDebug() << "Couldn't find ground texture file.";
    }
    if (!box.loadFromFile("C:/Users/ryant_000/Downloads/typersblock/MainMenu/box.png"))
    {
        qDebug () << "Couldn't find box texture file.";
    }
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
            std::cout << "Box at: " << bodyIt->GetPosition().x * SCALE << "," << bodyIt->GetPosition().y * SCALE << std::endl;
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
	sprite.rotate(clock.getElapsedTime().asSeconds() * 100.f);
	//Draw the sprite
	RenderWindow::draw(sprite);
	//Reset clock variable
	clock.restart();
}

void SFMLCanvas::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->QWidget::close();
    }
    qDebug() << event->text();
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
