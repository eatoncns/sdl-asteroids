#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ImageLoader.hpp> // TODO fwd declare when def in cpp

namespace pjm
{
    // struct ImageLoader;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader)
                : _imageLoader(iImageLoader)
            {}

            bool initialise()
            {
                return _imageLoader.loadFromFile("resources/Ship.gif");
            }

        private:
            ImageLoader& _imageLoader;
    };
}

#endif
