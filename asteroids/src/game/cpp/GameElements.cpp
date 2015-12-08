#include <GameElements.hpp>
#include <Ship.hpp>
#include <ShipAction.hpp>
#include <Asteroid.hpp>
#include <Bullet.hpp>
#include <boost/foreach.hpp>

using boost::shared_ptr;
using std::list;

namespace
{
    bool isExpired(shared_ptr<pjm::MovingObject> iMovingObject)
    {
        return iMovingObject->isExpired();
    }
}

namespace pjm
{
    GameElements::GameElements(shared_ptr<Ship> iShip,
                               list<shared_ptr<Asteroid> > iAsteroids)
        : _ship(iShip),
          _asteroids(iAsteroids),
          _collisionInteractions(new CollisionInteractions(_ship, _asteroids, _bullets))
    {}


    bool GameElements::update(const ShipAction& iAction, unsigned int iTimeElapsed)
    {
        updateAsteroids(iTimeElapsed);
        updateBullets(iTimeElapsed);
        updateShip(iAction, iTimeElapsed);
        handleCollisions();
        removeExpiredAsteroids();
        removeExpiredBullets();
        return _ship->isExpired();
    }


    void GameElements::updateShip(const ShipAction& iAction, unsigned int iTimeElapsed)
    {
        shared_ptr<Bullet> bullet = _ship->update(iAction, iTimeElapsed);
        if (bullet)
        {
            _bullets.push_back(bullet);
        }
    }


    void GameElements::updateAsteroids(unsigned int iTimeElapsed)
    {
        BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
        {
            asteroid->update(iTimeElapsed);
        }
    }


    void GameElements::updateBullets(unsigned int iTimeElapsed)
    {
        BOOST_FOREACH(shared_ptr<Bullet> bullet, _bullets)
        {
            bullet->update(iTimeElapsed);
        }
    }


    void GameElements::handleCollisions()
    {
        _collisionInteractions->update();
    }


    void GameElements::removeExpiredBullets()
    {
        _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), isExpired),
                       _bullets.end());
    }


    void GameElements::removeExpiredAsteroids()
    {
        _asteroids.erase(std::remove_if(_asteroids.begin(), _asteroids.end(), isExpired),
                         _asteroids.end());
    }


    void GameElements::render()
    {
        _ship->render();
        BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
        {
            asteroid->render();
        }
        BOOST_FOREACH(shared_ptr<Bullet> bullet, _bullets)
        {
            bullet->render();
        }
    }

    void GameElements::overrideCollisionInteractions(
        shared_ptr<CollisionInteractions> iCollisionInteractions)
    {
        _collisionInteractions = iCollisionInteractions;
    }
}
