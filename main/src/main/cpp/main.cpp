#include <GameLoop.hpp>
#include <SDLGame.hpp>

using namespace pjm;

int main()
{
    SDLGame game("Asteroids", 640, 480);
    GameLoop gameLoop(game);
    if (gameLoop.run())
    {
        return 0;
    }
    return -1;
}
