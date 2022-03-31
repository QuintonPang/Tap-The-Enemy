#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 3;
    this->mouseHeld = false;
    this->gameOver = false;
    this->health = 20;
    this->points = 0;
}

void Game::initWindow()
{
    this->videoMode.height=600;
    this->videoMode.width=600;

    this->window = new sf::RenderWindow(this->videoMode,"Tap The Enemy", sf::Style::Titlebar|sf::Style::Close);
    this->window->setFramerateLimit(80); // set frame rate limit
}

void Game::initFonts()
{
    if(this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout<<"Font has been successfully loaded";
    }
    else
    {
        std::cout<<"Font failed to load";

    }
}

void Game::initTexts()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                // check if key is esc to close window
                if(this->ev.key.code==sf::Keyboard::Escape)
                {
                    this->window->close();
                } 
                break;
        }
    }
}

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

const bool Game::isGameOver() const
{
    return this->gameOver;
}

void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
    // getting all events
    this->pollEvents();

    if(!this->gameOver)
    {
    this->updateMousePositions();
    this->updateEnemy();
    this->updateText();
    }

    // game over condition
    if(this->health<=0)
    {
        this->gameOver = true;
    }
}

void Game::spawnEnemy()
{
    // set at random x and 0 y
    // static cast means change varibale type
    // . is evaluated first, only then ->, so it must be two -> in this case
    this->enemy.setPosition(static_cast<float>(rand()%static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),0.f);
    this->enemy.setSize(sf::Vector2f(50.f,50.f));
    this->enemy.setFillColor(sf::Color::Red);

    // enemy to enemies list
    this->enemies.push_back(this->enemy);
}

void Game::updateEnemy()
{
    if(this->enemies.size()<this->maxEnemies) // if less than max enemies
    {
        if(this->enemySpawnTimer>=this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimerMax = 0; // reset timer after spawning
        }
        else
        {
            this->enemySpawnTimer++; // increment spawn timer
        }
    }

    // moving and updating the enemies
    for(int i=0;i<enemies.size();i++)
    {
        // bool deleted = false; // not deleting when moving
        this->enemies[i].move(0.f,5.f); // move enemy downwards
        if(this->enemies[i].getPosition().y>this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin()+i); // erase out of bound enemy
            this->health-- ;
        }
    }

    // remove enemy if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld==false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            // size_t is unsigned version of int
            for(size_t i = 0;i<this->enemies.size()&&deleted==false;i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // remove enemy when clicked
                    deleted = true;
                    // begin returns iterator pointing to first element
                    this->enemies.erase(this->enemies.begin()+i);
                    this->points += 10;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::updateText()
{
    std::stringstream ss;
    ss<<"Points: "<<this->points<<"\n"<<"Health: "<<this->health<<"\n";
    this->uiText.setString(ss.str());
}

void Game::renderEnemy(sf::RenderTarget& target)
{

    for(auto &e:this->enemies) // auto means it will be automatically deducted from its initializer
    {
        target.draw(e);
    }
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}

void Game::render()
{
    // clear frame for next frame
    this->window->clear(/*sf::Color::Red*/);
    this->renderEnemy(*this->window);
    this->renderText(*this->window);
    this->window->display();
}

// Constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
}

// Destructor
Game::~Game()
{
    delete this->window;
}
