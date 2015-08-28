#include <GameLoop.hpp>
#include <Game.hpp>

namespace pjm
{
    GameLoop::GameLoop(Game& iGame)
        : _game(iGame)
    {}


    void GameLoop::run()
    {
        if (!_game.initialise())
        {
            return;
        }
        while (_game.isRunning())
        {
            _game.update();
            _game.draw();
        }
    }
}

