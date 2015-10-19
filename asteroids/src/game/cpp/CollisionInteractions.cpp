#include <CollisionInteractions.hpp>
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <Bullet.hpp>
#include <Rectangle.hpp>
#include <boost/foreach.hpp>

using boost::shared_ptr;
using std::list;

namespace pjm
{
    CollisionInteractions::CollisionInteractions(shared_ptr<Ship> iShip,
                                                 list<shared_ptr<Asteroid> >& iAsteroids,
                                                 list<shared_ptr<Bullet> >& iBullets)
        : _collisionDetector(new CollisionDetector()),
          _ship(iShip),
          _asteroids(iAsteroids),
          _bullets(iBullets)
    {}


    void CollisionInteractions::update()
    {
        handleShipCollision();
        if (_ship->isExpired())
        {
            return;
        }
        handleAsteroidCollisions();
        handleBulletCollisions();
    }


    void CollisionInteractions::handleShipCollision()
    {
        BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
        {
            if (_collisionDetector->areColliding(_ship->getBoundingBox(),
                                                 asteroid->getBoundingBox()))
            {
                _ship->collideWith(asteroid.get());
            }
        }
    }


    void CollisionInteractions::handleAsteroidCollisions()
    {
        if (_asteroids.size() < 2)
        {
            return;
        }
        typedef list<shared_ptr<Asteroid> >::iterator asteroid_it;
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
                    (*outerIt)->collideWith(innerIt->get());
                }
            }
        }
    }


    void CollisionInteractions::handleBulletCollisions()
    {
        BOOST_FOREACH(shared_ptr<Bullet> bullet, _bullets)
        {
            BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
            {
                if (_collisionDetector->areColliding(bullet->getBoundingBox(),
                                                     asteroid->getBoundingBox()))
                {
                        //asteroid->collideWith(bullet.get());
                        //bullet->collideWith(asteroid.get());
                }
            }
        }
    }
}
