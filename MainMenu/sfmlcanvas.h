#ifndef SFML_CANVAS_H
#define SFML_CANVAS_H
#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <QPushButton>

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
    QTimer repaintTimer;
    QTimer gameTimer;
    QWidget* prev;
    QPushButton quitButton;

	sf::Clock clock;
    sf::Texture pauseTexture;
    sf::Texture ground;
    sf::Texture box;

    int numMistakes;
    int lessonNum;

    sf::String TextString;
    sf::String DisplayString;
    sf::Font Font;
    sf::Text DisplayText;
    sf::Text Text;
    size_t index;

    //sf::Sprite sprite;
	bool initialized;
    bool paused = false;
    b2Vec2* gravity;
    b2World* world;
    void makeGround(int x, int y);
    void makeBox(int x, int y);
    void pause();
    void play();

    sf::String getNextLesson(int);


private slots:
    void keyPressEvent(QKeyEvent *);
};
#endif SFML_CANVAS_H
