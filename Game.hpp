// header file

#pragma once // means that this file can be used once only
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
class Game
{
private:
    
    // variables for setting up window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // mouse positions
    sf::Vector2i mousePosWindow; // ( relative to window )
    sf::Vector2f mousePosView;

    // variables for enemies
    int maxEnemies;
    float enemySpawnTimer; // current timer
    float enemySpawnTimerMax; // max timer
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies; // list of enemies

    bool mouseHeld; // to prevent clicking while dragging

    bool gameOver;

    unsigned points; // unsigned means the value wil not be negative
    int health;

    // fonts
    sf::Font font;

    // texts
    sf::Text uiText;

    // initializing variables
    void initVariables();
    
    // function for setting up window
    void initWindow();

    // function for importing fonts
    void initFonts();

    // function for writing texts
    void initTexts();

    // function for getting all events
    void pollEvents();

    // spawn enemies 
    void spawnEnemy();

    // update enemy
    void updateEnemy();

    // render enemy
    void renderEnemy(sf::RenderTarget &target); // can be rendered on any render target

    // update and render texts
    void updateText();
    void renderText(sf::RenderTarget &target); 

    // updates
    void updateMousePositions();

public:
    // constructor

    Game();

    // destructor (executes after object is destroyed)
    virtual ~Game();

    // check if game is running
    const bool isRunning() const;

    // check if game over
    const bool isGameOver() const;
   
    // functions
    void update();
    void render();
};
