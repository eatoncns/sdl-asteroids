#include <GameLoop.hpp>
#include <Game.hpp>

namespace pjm
{
    GameLoop::GameLoop(Game& iGame, Timer& iTimer)
        : _game(iGame), _timer(iTimer)
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

