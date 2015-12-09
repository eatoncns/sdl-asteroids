#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <ScreenWrappingObject.hpp>
#include <Vector.hpp>

namespace pjm
{
    class Asteroid;
    class Bullet;
    class BulletLoader;
    struct ShipAction;

    class Ship : public ScreenWrappingObject
    {
        public:
            Ship(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                 boost::shared_ptr<BulletLoader> iBulletLoader);

            virtual boost::shared_ptr<Bullet> update(const ShipAction& iAction,
                                                     unsigned int iTimeElapsed);

            virtual void collideWith(Asteroid* iAsteroid);

            virtual std::string imageFilePath();

            virtual ~Ship() {}

            static const float ACC_FACTOR = 0.0001;
            static const double ROTATION_FACTOR = 0.1;
            static const float MAX_VELOCITY = 0.1;

        private:
            void updateAngle(const ShipAction& iAction, unsigned int iTimeElapsed);
            void updateAcceleration(const ShipAction& iAction);
            void updateVelocity(unsigned int iTimeElapsed);
            boost::shared_ptr<Bullet> handleShooting(const ShipAction& iAction);

            Vector _acceleration;
            boost::shared_ptr<BulletLoader> _bulletLoader;
    };
}

#endif
