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
            
            enum Action {NONE, ACCELERATE};

            virtual void update(const Action iAction, unsigned int iTimeElapsed);
            virtual void render();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.000001;

        private:
            Vector _location;
            Vector _previousLocation;
            Vector _acceleration;
            Renderable& _image;
    };
}

#endif
