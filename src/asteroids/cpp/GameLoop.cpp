#include <GameLoop.hpp>
#include <Game.hpp>

namespace pjm
{
    GameLoop::GameLoop(Game& iGame)
        : _game(iGame)
    {}


    bool GameLoop::run()
    {
        if (!_game.initialise())
        {
            return false;
        }
        while (_game.isRunning())
        {
            _game.update();
            _game.draw();
        }
        return true;
    }
}

