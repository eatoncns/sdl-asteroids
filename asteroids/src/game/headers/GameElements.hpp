#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ScreenInfo.hpp>
#include <KeyPress.hpp>

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
            
            Ship* _ship;

        private:
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
    };
}

#endif
