#include <GameLoop.hpp>
#include <Game.hpp>

namespace pjm
{
    GameLoop::GameLoop(Game& iGame)
        : _game(iGame)
    {}


    void GameLoop::run()
    {
        _game.initialise();
        while (_game.isRunning())
        {
            _game.update();
            _game.draw();
        }
    }
}

