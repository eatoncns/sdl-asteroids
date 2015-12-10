#ifndef _PJM_ASTEROID_HPP_
#define _PJM_ASTEROID_HPP_

namespace pjm
{
    class Bullet;
    class ImageLoader;
    class RandomGenerator;
    class Rectangle;
    class Vector;

    struct Asteroid
    {
        virtual bool initialise(const Vector& iInitialLocation,
                        ImageLoader& iImageLoader,
                        RandomGenerator& iRandomGenerator) = 0;

        virtual void update(unsigned int iTimeElapsed) = 0;

        virtual void render() = 0;

        virtual Rectangle getBoundingBox() = 0;

        virtual void collideWith(Asteroid* iOther) = 0;

        virtual void collideWith(Bullet* iBullet) = 0;

        virtual bool isExpired() = 0;

        virtual Vector getNormalisedDirection() = 0;
        virtual void setNormalisedDirection(const Vector& iNormalisedDirection) = 0;
    };
}

#endif /* end of include guard: _PJM_ASTEROID_HPP_ */
