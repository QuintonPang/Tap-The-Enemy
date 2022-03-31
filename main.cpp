#include <SFML/Graphics.hpp>
#include "Game.cpp"
using namespace sf;

int main()
{
    Game game;
    while(game.isRunning()&&!game.isGameOver())
    {
        game.update();
        game.render();
    }
    return 0;
}
