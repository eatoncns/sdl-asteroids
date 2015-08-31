#include <GameLoop.hpp>
#include <SDLGame.hpp>
#include <SDLTimer.hpp>
#include <ScreenInfo.hpp>

using namespace pjm;

int main()
{
    ScreenInfo screenInfo("Asteroids", 720, 540);
    SDLGame game(screenInfo);
    SDLTimer timer;
    GameLoop gameLoop(game, timer);
    if (gameLoop.run())
    {
        return 0;
    }
    return -1;
}
