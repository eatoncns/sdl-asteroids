#ifndef _PJM_SDLGAME_HPP_
#define _PJM_SDLGAME_HPP_

#include <Game.hpp>
#include <ScreenInfo.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

class SDL_Window;
class SDL_Renderer;

namespace pjm
{
    struct ImageLoader;
    class ScreenWrapper;
    class GameElements;
    class Ship;
    class Asteroid;

    class SDLGame : public Game
    {
        public:
            SDLGame(const ScreenInfo& iScreenInfo);
            ~SDLGame();

            bool initialise();
            bool isRunning();
            void update(unsigned int iTimeElapsed);
            void draw();

        private:

            bool initSDL();
            bool initWindow();
            bool initRenderer();
            bool initGameElements();
            boost::shared_ptr<Ship> createShip(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                               ImageLoader& iImageLoader);
            std::list<boost::shared_ptr<Asteroid> > createAsteroids(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                                                    ImageLoader& iImageLoader);
            void startGame();

            ScreenInfo _screenInfo;
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            bool _running;
            boost::scoped_ptr<GameElements> _gameElements;
    };
}

#endif
