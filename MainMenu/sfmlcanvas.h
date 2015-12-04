#ifndef SFML_CANVAS_H
#define SFML_CANVAS_H
#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include <Box2D/Box2D.h>

class SFMLCanvas : public QWidget, public sf::RenderWindow
{
	//Q_OBJECT
public:
	SFMLCanvas(QWidget * parent, const QPoint& position, const QSize& size, int frameTime = 0);
	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;
	virtual void paintEvent(QPaintEvent*);
	virtual ~SFMLCanvas();
	virtual void initialize();
	virtual void update();
private:
	QTimer timer;
	sf::Clock clock;
	sf::Texture texture;
	sf::Sprite sprite;
	bool initialized;
    b2Vec2* gravity;
    b2World* world;
};
#endif SFML_CANVAS_H
