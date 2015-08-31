#include <GameLoop.hpp>
#include <Game.hpp>
#include <Timer.hpp>

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
        unsigned int previousTime = _timer.getTime();
        while (_game.isRunning())
        {
            unsigned int currentTime = _timer.getTime();
            _game.update(currentTime - previousTime);
            _game.draw();
            previousTime = currentTime;
        }
        return true;
    }
}

