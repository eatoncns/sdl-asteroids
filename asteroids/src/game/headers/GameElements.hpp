#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ScreenInfo.hpp>
#include <ScreenWrapper.hpp>
#include <KeyPress.hpp>
#include <boost/function.hpp>
#include <list>

namespace pjm
{
    struct ImageLoader;
    struct RandomGenerator;
    class Ship;
    class Asteroid;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader,
                         const ScreenInfo& iScreenInfo);

            ~GameElements();

            bool initialise();

            void update(keyboard::KeyPress iKeyPress, unsigned int iTimeElapsed);

            void render();
             
            typedef boost::function<Ship*(ImageLoader& iImage, 
                                          ScreenWrapper& iScreenWrapper)> ship_creator;
            ship_creator _shipCreator;

            typedef boost::function<Asteroid*(ImageLoader& iImage,
                                              ScreenWrapper& iScreenWrapper,
                                              RandomGenerator& iRandomGenerator)> asteroid_creator;
            asteroid_creator _asteroidCreator;

            static const int NUM_ASTEROIDS = 1;

        private:
            bool initialiseShip();
            bool initialiseAsteroids();

            Ship* _ship;
            std::list<Asteroid*> _asteroids;
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
            ScreenWrapper _screenWrapper;
    };
}

#endif
