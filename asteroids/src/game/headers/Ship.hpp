#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <Vector.hpp>

namespace pjm
{
    struct Renderable;
    struct ImageLoader;

    class Ship
    {
        public:
            Ship(ImageLoader& iImageLoader);
            
            enum Action {NONE, ACCELERATE};

            virtual bool initialise(const Vector& iInitialLocation);
            virtual void update(const Action iAction, unsigned int iTimeElapsed);
            virtual void render();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.000001;

            static Ship* create(ImageLoader& iImageLoader);

        private:
            Vector _location;
            Vector _previousLocation;
            Vector _acceleration;
            ImageLoader& _imageLoader;
            Renderable* _image;
    };
}

#endif
