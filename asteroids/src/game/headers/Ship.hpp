#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <Coordinate.hpp>

namespace pjm
{
    struct Renderable;

    class Ship
    {
        public:
            Ship(Coordinate iInitialLocation, Renderable& iImage);

            void render();

        private:
            Coordinate _location;
            Renderable& _image;
    };
}

#endif
