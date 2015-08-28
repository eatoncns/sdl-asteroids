#include <GameLoop.hpp>
#include <Game.hpp>

namespace pjm
{
    GameLoop::GameLoop(Game& iGame)
        : _game(iGame)
    {}


    void GameLoop::run()
    {
        while (_game.isRunning())
        {
            _game.update();
        }
    }
}

