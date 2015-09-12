#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <Vector.hpp>

namespace pjm
{
    struct Renderable;
    struct ImageLoader;
    struct ScreenWrapper;

    class Ship
    {
        public:
            Ship(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper);
            
            enum Action {NONE, ACCELERATE, TURN_LEFT, TURN_RIGHT, ACCELERATE_LEFT, ACCELERATE_RIGHT};

            virtual bool initialise(const Vector& iInitialLocation);
            virtual void update(const Action iAction, unsigned int iTimeElapsed);
            virtual void render();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.0001;
            static const double ROTATION_FACTOR = 0.1;
            static const float MAX_VELOCITY = 0.1;

            static Ship* create(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper);

        protected:
            void updateAngle(const Action iAction, unsigned int iTimeElapsed);
            void updateAcceleration(const Action iAction);
            void updateVelocity(unsigned int iTimeElapsed);
            void updateLocation(unsigned int iTimeElapsed);
            void handleScreenWrap(unsigned int iTimeElapsed);

            Vector _location;
            Vector _velocity;
            Vector _acceleration;
            double _angle;
            ScreenWrapper& _screenWrapper;
            ImageLoader& _imageLoader;
            Renderable* _image;
    };
}

#endif
