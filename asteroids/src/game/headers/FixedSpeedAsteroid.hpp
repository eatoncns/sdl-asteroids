#ifndef _PJM_FIXEDSPEEDASTEROID_HPP_
#define _PJM_FIXEDSPEEDASTEROID_HPP_

#include <Asteroid.hpp>
#include <ObjectRenderer.hpp>
#include <PhysicsData.hpp>
#include <boost/shared_ptr.hpp>

namespace pjm
{
    class ScreenWrapper;

    class FixedSpeedAsteroid : public Asteroid
    {
        public:
            FixedSpeedAsteroid(boost::shared_ptr<ScreenWrapper> iScreenWrapper);

            bool initialise(const Vector& iInitialLocation,
                            ImageLoader& iImageLoader,
                            RandomGenerator& iRandomGenerator);

            void update(unsigned int iTimeElapsed);

            void render();

            Rectangle getBoundingBox();

            void collideWith(Asteroid* iOther);

            void collideWith(Bullet* iBullet);

            bool isExpired();

            Vector getNormalisedDirection();
            void setNormalisedDirection(const Vector& iNormalisedDirection);

            static const float VELOCITY;

        private:
            static const std::string imageFilePath;

            ObjectRenderer _renderer;
            PhysicsData _physicsData;
            boost::shared_ptr<ScreenWrapper> _screenWrapper;
            bool _expired;
    };
}

#endif
