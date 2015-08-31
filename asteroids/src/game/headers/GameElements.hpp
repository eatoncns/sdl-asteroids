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
            
            Ship* _ship; // public for test purposes

        private:
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
    };
}

#endif
