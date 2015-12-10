#ifndef _PJM_FIXEDSPEEDBULLET_HPP_
#define _PJM_FIXEDSPEEDBULLET_HPP_

#include <Bullet.hpp>
#include <ObjectRenderer.hpp>
#include <PhysicsData.hpp>
#include <Vector.hpp>

namespace pjm
{
    class FixedSpeedBullet : public Bullet
    {
        public:
            FixedSpeedBullet(const Vector& iBounds);

            bool initialise(const Vector& iInitialLocation,
                            const double iAngle,
                            ImageLoader& iImageLoader);

            void update(unsigned int iTimeElapsed);

            void render();

            Rectangle getBoundingBox();

            void collideWith(Asteroid* iAsteroid);

            bool isExpired();

            static const float VELOCITY;

        private:
            static const std::string imageFilePath;
            bool isOutsideOfScreen();

            ObjectRenderer _renderer;
            PhysicsData _physicsData;
            Vector _bounds;
            bool _expired;

    };
}

#endif
