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
            
            enum Action {ACCELERATE};

            void update(const Action iAction, int iTimeElapsed);
            void render();


            static const float ACC_FACTOR = 0.001;

        private:
            Vector _location;
            Vector _previousLocation;
            Vector _acceleration;
            Renderable& _image;
    };
}

#endif
