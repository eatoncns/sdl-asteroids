#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ScreenInfo.hpp>
#include <KeyPress.hpp>
#include <boost/function.hpp>

namespace pjm
{
    struct ImageLoader;
    class Ship;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader,
                         const ScreenInfo& iScreenInfo);

            ~GameElements();

            bool initialise();

            void update(keyboard::KeyPress iKeyPress, unsigned int iTimeElapsed);

            void render();
             
            typedef boost::function<Ship*(ImageLoader& iImage)> ship_creator;
            ship_creator _shipCreator;

        private:
            Ship* _ship;
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
    };
}

#endif
