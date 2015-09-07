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
            
            enum Action {NONE, ACCELERATE, TURN_LEFT, TURN_RIGHT};

            virtual bool initialise(const Vector& iInitialLocation, const Vector& iBounds);
            virtual void update(const Action iAction, unsigned int iTimeElapsed);
            virtual void render();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.000001;
            static const double ROTATION_FACTOR = 0.01;
            static const float MAX_VELOCITY = 0.2;

            static Ship* create(ImageLoader& iImageLoader);

        protected:
            void updateAngle(const Action iAction, unsigned int iTimeElapsed);
            void updateAcceleration(const Action iAction);
            void updateVelocity(unsigned int iTimeElapsed);
            void updateLocation(unsigned int iTimeElapsed);

            Vector _location;
            Vector _velocity;
            Vector _acceleration;
            double _angle;
            Vector _bounds;
            ImageLoader& _imageLoader;
            Renderable* _image;
    };
}

#endif
