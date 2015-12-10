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
    Q_OBJECT
public:
    SFMLCanvas(QWidget * parent, const QPoint& position, const QSize& size, int frameTime = 0);
    //Some public methods used to interface with Qt. We keep the opttion to inherit from this class open.
	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;
	virtual void paintEvent(QPaintEvent*);
	virtual ~SFMLCanvas();
	virtual void initialize();
	virtual void update();
private:
    //Various Qt constructs
    QTimer repaintTimer;
    QTimer gameTimer;
    QWidget* prev;
    //QPushButton quitButton;

    //Used to draw smooth animations, even while the scene may update more than 60 times a second
	sf::Clock clock;

    //Image textures
    sf::Texture pauseTexture;
    sf::Texture playTexture;
    sf::Texture backgroundTexture;

    int numMistakes;
    int lessonNum;

    //Various texts, strings, fonts, etc.
    //These are all used for drawing text to the screen - an important task for a typing game.
    sf::String textString;
    sf::String displayString;
    sf::Font textFont;
    sf::Font numberFont;
    sf::Text displayText;
    sf::Text userText;
    sf::Text timerText;
    sf::Text mistakeText;
    size_t index;

    //Some game state variables
    int state = 2;
    int gameTime = 0;
	bool initialized;

    //Box2D variables
    b2Vec2* gravity;
    b2World* world;

    //Private methods
    void makeGround(int x, int y);
    void makeDynamicBody(int x, int y);
    void pause();
    void play();
    //Sets up a sf::Text with some basic properties. Cuts down on code copying.
    void initializeText(sf::Text& text, int x, int y, const char* string);
    sf::String getNextLesson(int);


private slots:
    void keyPressEvent(QKeyEvent *);
    //Called every 10 seconds while the game is running.
    void updateGameTime();
};
#endif SFML_CANVAS_H