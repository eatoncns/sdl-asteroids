#ifndef _PJM_ASTEROIDCREATOR_HPP_
#define _PJM_ASTEROIDCREATOR_HPP_

#include <boost/shared_ptr.hpp>
#include <list>

namespace pjm
{
    class Asteroid;
    class ScreenWrapper;
    struct RandomGenerator;

    class AsteroidCreator
    {
        public:
            std::list<boost::shared_ptr<Asteroid> > create(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                                           RandomGenerator& iRandomGenerator);
    };
}

#endif
