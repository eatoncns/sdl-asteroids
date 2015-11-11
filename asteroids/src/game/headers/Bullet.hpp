#ifndef _PJM_BULLET_HPP_
#define _PJM_BULLET_HPP_

#include <CollidableObject.hpp>

namespace pjm
{
    struct Vector;
    struct ImageLoader;
    class Asteroid;

    class Bullet : public CollidableObject
    {
        public:
            Bullet(const Vector& iBounds);

            virtual bool initialise(const Vector& iInitialLocation,
                            const double iAngle,
                            ImageLoader& iImageLoader);

            virtual void update(unsigned int iTimeElapsed);

            virtual void collideWith(Asteroid* iAsteroid);

            virtual ~Bullet() {}

            static const float VELOCITY;

        private:
            std::string imageFilePath();
            bool isOutsideOfScreen();

            Vector _bounds;

    };
}

#endif
