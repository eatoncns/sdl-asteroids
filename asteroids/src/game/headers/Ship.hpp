#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <ScreenWrappingObject.hpp>
#include <Vector.hpp>

namespace pjm
{
    class Asteroid;

    class Ship : public ScreenWrappingObject
    {
        public:
            Ship(boost::shared_ptr<ScreenWrapper> iScreenWrapper);

            enum Action {NONE, ACCELERATE, TURN_LEFT, TURN_RIGHT, ACCELERATE_LEFT, ACCELERATE_RIGHT};

            virtual void update(const Action iAction, unsigned int iTimeElapsed);

            void collideWith(Asteroid* iAsteroid);

            virtual std::string imageFilePath();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.0001;
            static const double ROTATION_FACTOR = 0.1;
            static const float MAX_VELOCITY = 0.1;

        protected:
            void updateAngle(const Action iAction, unsigned int iTimeElapsed);
            void updateAcceleration(const Action iAction);
            void updateVelocity(unsigned int iTimeElapsed);

            Vector _acceleration;
    };
}

#endif
