#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <Coordinate.hpp>
#include <Renderable.hpp> // TODO: fwd declare when defs in cpp

namespace pjm
{
    struct Renderable;

    class Ship
    {
        public:
            Ship(Coordinate iInitialLocation,
                 Renderable& iImage)
                : _location(iInitialLocation),
                  _image(iImage)
            {}

            void render()
            {
                _image.render(_location);
            }

        private:
            Coordinate _location;
            Renderable& _image;
    };
}

#endif
