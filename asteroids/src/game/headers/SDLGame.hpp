#ifndef _PJM_SDLGAME_HPP_
#define _PJM_SDLGAME_HPP_

#include <Game.hpp>
#include <string>

class SDL_Window;
class SDL_Renderer;

namespace pjm
{
    class SDLGame : public Game
    {
        public:
            SDLGame(const std::string& iGameName,
                    int iScreenWidth,
                    int iScreenHeight);
            ~SDLGame();

            bool initialise();
            bool isRunning();
            void update();
            void draw();

        private:

            bool initSDL();
            bool initWindow();
            bool initRenderer();
            void startGame();

            std::string _gameName;
            int _screenWidth;
            int _screenHeight;
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            bool _running;
    };
}

#endif
