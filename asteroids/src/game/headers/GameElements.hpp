#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ScreenInfo.hpp>
#include <Ship.hpp>

namespace pjm
{
    struct ImageLoader;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader,
                         const ScreenInfo& iScreenInfo);

            ~GameElements();

            bool initialise();

            void render();
            


        private:
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
            Ship* _ship;
    };
}

#endif
