#ifndef _PJM_BULLET_HPP_
#define _PJM_BULLET_HPP_

#include <CollidableObject.hpp>

namespace pjm
{
    struct Vector;
    struct ImageLoader;

    class Bullet : public CollidableObject
    {
        public:
            Bullet(const Vector& iBounds);

            bool initialise(const Vector& iInitialLocation,
                            const Vector& iShooterVelocity,
                            ImageLoader& iImageLoader);

            void update(unsigned int iTimeElapsed);

            static const float VELOCITY = 1.02;

        private:
            std::string imageFilePath();
            bool isOutsideOfScreen();

            Vector _bounds;

    };
}

#endif
