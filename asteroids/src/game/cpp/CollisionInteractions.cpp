#include <CollisionInteractions.hpp>
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <Rectangle.hpp>
#include <boost/foreach.hpp>

namespace pjm
{
    CollisionInteractions::CollisionInteractions(Ship* iShip, std::list<Asteroid*>& iAsteroids)
        : _collisionDetector(new CollisionDetector()),
          _ship(iShip), 
          _asteroids(iAsteroids)
    {}

    
    bool CollisionInteractions::update()
    {
        if (shipIsColliding())
        {
            return true;
        }
        handleAsteroidCollisions();
        return false;
    }


    bool CollisionInteractions::shipIsColliding()
    {
        BOOST_FOREACH(Asteroid* asteroid, _asteroids)
        {
            if (_collisionDetector->areColliding(_ship->getBoundingBox(), 
                                                 asteroid->getBoundingBox()))
            {
                return true;
            }
        }
        return false;
    }


    void CollisionInteractions::handleAsteroidCollisions()
    {
        if (_asteroids.size() < 2)
        {
            return;
        }
        typedef std::list<Asteroid*>::iterator asteroid_it;
        asteroid_it outerIt = _asteroids.begin();
        asteroid_it lastIt = _asteroids.end()--;
        for ( ; outerIt != lastIt; ++outerIt)
        {
            asteroid_it innerIt = outerIt;
            ++innerIt;
            for ( ; innerIt != _asteroids.end(); ++innerIt)
            {
                if (_collisionDetector->areColliding((*outerIt)->getBoundingBox(),
                                                     (*innerIt)->getBoundingBox()))
                {
                    (*outerIt)->collideWith(*innerIt);
                }
            }
        }
    }
}
