#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <MovingObject.hpp>
#include <Vector.hpp>

namespace pjm
{

    class Ship : public MovingObject
    {
        public:
            Ship(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper);
            
            enum Action {NONE, ACCELERATE, TURN_LEFT, TURN_RIGHT, ACCELERATE_LEFT, ACCELERATE_RIGHT};

            virtual void update(const Action iAction, unsigned int iTimeElapsed);

            virtual std::string imageFilePath();

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
            
            Vector _acceleration;
    };
}

#endif
