#ifndef _PJM_ASTEROID_HPP_
#define _PJM_ASTEROID_HPP_

#include <ScreenWrappingObject.hpp>

namespace pjm
{
    struct RandomGenerator;
    class Bullet;

    class Asteroid : public ScreenWrappingObject
    {
        public:
            Asteroid(boost::shared_ptr<ScreenWrapper> iScreenWrapper);

            virtual bool initialise(const Vector& iInitialLocation,
                                    ImageLoader& iImageLoader,
                                    RandomGenerator& iRandomGenerator);

            virtual void update(unsigned int iTimeElapsed);

            virtual void collideWith(Asteroid* iOther);
            virtual void collideWith(Bullet* iBullet);

            virtual ~Asteroid() {}

            static float VELOCITY;

            virtual std::string imageFilePath();
    };
}

#endif
