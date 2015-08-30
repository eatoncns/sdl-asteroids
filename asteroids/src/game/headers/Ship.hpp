#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <Vector.hpp>

namespace pjm
{
    struct Renderable;

    class Ship
    {
        public:
            Ship(const Vector& iInitialLocation, Renderable& iImage);

            void render();

        private:
            Vector _location;
            Renderable& _image;
    };
}

#endif
