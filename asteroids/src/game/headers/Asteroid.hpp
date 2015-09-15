#ifndef _PJM_ASTEROID_HPP_
#define _PJM_ASTEROID_HPP_

#include <MovingObject.hpp>

namespace pjm
{
    struct RandomGenerator;

    class Asteroid : public MovingObject
    {
        public:
            Asteroid(ImageLoader& iImageLoader, 
                     ScreenWrapper& iScreenWrapper, 
                     RandomGenerator& iRandomGenerator);
            
            virtual bool initialise(const Vector& iInitialLocation);

            virtual void update(unsigned int iTimeElapsed);
            
            virtual ~Asteroid() {}

            static Asteroid* create(ImageLoader& iImageLoader,
                                    ScreenWrapper& iScreenWrapper,
                                    RandomGenerator& iRandomGenerator);

            static float VELOCITY;

        protected:
            virtual std::string imageFilePath();
            
            RandomGenerator& _random;
    };
}

#endif
