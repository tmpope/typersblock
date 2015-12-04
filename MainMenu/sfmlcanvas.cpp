#include "sfmlcanvas.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "qdebug.h"
#include "Box2D/Box2D.h"
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
    //gravity = new b2Vec2(0.0f, -10.0f);
    //world = new b2World(*gravity);
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
}

void SFMLCanvas::update()
{
	//clear the window
	RenderWindow::clear(sf::Color(0, 0, 0));
	//Rotate 100 degrees per second
	sprite.rotate(clock.getElapsedTime().asSeconds() * 100.f);
	//Draw the sprite
	RenderWindow::draw(sprite);
	//Reset clock variable
	clock.restart();
}
