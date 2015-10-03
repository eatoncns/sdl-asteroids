#ifndef _PJM_ASTEROID_HPP_
#define _PJM_ASTEROID_HPP_

#include <MovingObject.hpp>

namespace pjm
{
    struct RandomGenerator;

    class Asteroid : public MovingObject
    {
        public:
            Asteroid(boost::shared_ptr<ScreenWrapper> iScreenWrapper, 
                     RandomGenerator& iRandomGenerator);
            
            virtual bool initialise(const Vector& iInitialLocation,
                                    ImageLoader& iImageLoader);

            virtual void update(unsigned int iTimeElapsed);

            virtual void collideWith(Asteroid* iOther);
            
            virtual ~Asteroid() {}

            static float VELOCITY;

        protected:
            virtual std::string imageFilePath();
            
            RandomGenerator& _random;
    };
}

#endif
