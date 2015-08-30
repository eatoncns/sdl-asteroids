#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ScreenInfo.hpp>
#include <Ship.hpp>
#include <boost/scoped_ptr.hpp>

namespace pjm
{
    struct ImageLoader;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader,
                         const ScreenInfo& iScreenInfo);

            bool initialise();

            void render();

        private:
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
            boost::scoped_ptr<Ship> _ship;
    };
}

#endif
