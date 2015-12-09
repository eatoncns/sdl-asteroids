#ifndef _PJM_EULERSHIP_HPP_
#define _PJM_EULERSHIP_HPP_

#include <ObjectRenderer.hpp>
#include <PhysicsData.hpp>
#include <Ship.hpp>
#include <Vector.hpp>
#include <boost/shared_ptr.hpp>

namespace pjm
{
    class Asteroid;
    class Bullet;
    class BulletLoader;
    class ScreenWrapper;
    struct ShipAction;

    class EulerShip : public Ship
    {
        public:
            EulerShip(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                      boost::shared_ptr<BulletLoader> iBulletLoader);

            bool initialise(const Vector& iInitialLocation,
                            ImageLoader& iImageLoader);

            boost::shared_ptr<Bullet> update(const ShipAction& iAction,
                                                     unsigned int iTimeElapsed);

            void render();

            Rectangle getBoundingBox();

            void collideWith(Asteroid* iAsteroid);

            bool isExpired();

            static const float ACC_FACTOR = 0.0001;
            static const double ROTATION_FACTOR = 0.1;
            static const float MAX_VELOCITY = 0.1;

        private:
            static const std::string imageFilePath;

            void updateAngle(const ShipAction& iAction, unsigned int iTimeElapsed);
            void updateAcceleration(const ShipAction& iAction);
            void updateVelocity(unsigned int iTimeElapsed);
            void updateLocation(unsigned int iTimeElapsed);
            void handleScreenWrap(unsigned int iTimeElapsed);
            boost::shared_ptr<Bullet> handleShooting(const ShipAction& iAction);

            ObjectRenderer _renderer;
            PhysicsData _physicsData;
            double _angle;
            Vector _acceleration;
            bool _expired;
            boost::shared_ptr<ScreenWrapper> _screenWrapper;
            boost::shared_ptr<BulletLoader> _bulletLoader;
    };
}

#endif
