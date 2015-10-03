#ifndef _PJM_ASTEROIDCREATOR_HPP_
#define _PJM_ASTEROIDCREATOR_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

namespace pjm
{
    class Asteroid;
    class ScreenWrapper;
    struct ImageLoader;
    struct RandomGenerator;
    class LocationGenerator;

    class AsteroidCreator
    {
        public:
            std::list<boost::shared_ptr<Asteroid> > create(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                                           ImageLoader& iImageLoader,
                                                           LocationGenerator& iLocationGenerator,
                                                           RandomGenerator& iRandomGenerator);
            
            const static int NUM_ASTEROIDS = 5;

        protected:
            virtual boost::shared_ptr<Asteroid> makeAsteroid(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                                             RandomGenerator& iRandomGenerator);
    };
}

#endif
