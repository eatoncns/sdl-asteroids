#include <AsteroidCreator.hpp>
#include <Asteroid.hpp>
#include <ScreenWrapper.hpp>
#include <LocationGenerator.hpp>
#include <RandomGenerator.hpp>

using boost::shared_ptr;
using std::list;

namespace pjm
{
    list<shared_ptr<Asteroid> > AsteroidCreator::create(shared_ptr<ScreenWrapper> iScreenWrapper,
                                                        ImageLoader& iImageLoader,
                                                        LocationGenerator& iLocationGenerator,
                                                        RandomGenerator& iRandomGenerator)
    {
        list<shared_ptr<Asteroid> > asteroids;
        float minDistanceFromCentre = 150.0;
        float maxDistanceFromCentre = 250.0;
        for (int i = 0; i < NUM_ASTEROIDS; ++i)
        {
            shared_ptr<Asteroid> asteroid = makeAsteroid(iScreenWrapper);
            Vector initialLocation = iLocationGenerator.generateLocation(minDistanceFromCentre,
                                                                         maxDistanceFromCentre);
            if (!asteroid->initialise(initialLocation, iImageLoader, iRandomGenerator))
            {
                return list<shared_ptr<Asteroid> >();
            } 
            asteroids.push_back(asteroid);
        }
        return asteroids;
    }
            
    
    shared_ptr<Asteroid> AsteroidCreator::makeAsteroid(shared_ptr<ScreenWrapper> iScreenWrapper)
    {
        shared_ptr<Asteroid> asteroid(new Asteroid(iScreenWrapper));
        return asteroid;
    }
}
