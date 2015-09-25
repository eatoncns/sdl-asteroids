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

    
    void CollisionInteractions::update()
    {
        BOOST_FOREACH(Asteroid* asteroid, _asteroids)
        {
            _collisionDetector->areColliding(_ship->getBoundingBox(), 
                                             asteroid->getBoundingBox());
        }
    }
}
