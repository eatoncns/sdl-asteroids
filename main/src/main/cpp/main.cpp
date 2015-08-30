#include <GameLoop.hpp>
#include <SDLGame.hpp>
#include <ScreenInfo.hpp>

using namespace pjm;

int main()
{
    ScreenInfo screenInfo("Asteroids", 640, 480);
    SDLGame game(screenInfo);
    GameLoop gameLoop(game);
    if (gameLoop.run())
    {
        return 0;
    }
    return -1;
}
