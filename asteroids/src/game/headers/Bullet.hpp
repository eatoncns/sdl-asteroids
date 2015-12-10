#ifndef _PJM_BULLET_HPP_
#define _PJM_BULLET_HPP_

namspace pjm
{
    struct Bullet
    {
        virtual bool initialise(const Vector& iInitialLocation,
                                const double iAngle,
                                ImageLoader& iImageLoader) = 0;

        virtual void update(unsigned int iTimeElapsed) = 0;

        virtual void render() = 0;

        virtual Rectangle getBoundingBox() = 0;

        virtual void collideWith(Asteroid* iAsteroid) = 0;

        virtual bool isExpired() = 0;

        virtual ~Bullet() {}
    };
}

#endif /* end of include guard: _PJM_BULLET_HPP_ */
