#ifndef _PJM_ORDEREDCOLLISIONINTERACTIONS_HPP_
#define _PJM_ORDEREDCOLLISIONINTERACTIONS_HPP_

#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;
    class Bullet;

    class OrderedCollisionInteractions : public CollisionInteractions
    {
        public:
            OrderedCollisionInteractions(boost::shared_ptr<Ship> iShip,
                                  std::list<boost::shared_ptr<Asteroid> >& iAsteroids,
                                  std::list<boost::shared_ptr<Bullet> >& iBullets);

            void update();

            void overrideCollisionDetector(boost::shared_ptr<CollisionDetector> iCollisionDetector);

        private:
            void handleShipCollision();
            void handleAsteroidCollisions();
            void handleBulletCollisions();

            boost::shared_ptr<Ship> _ship;
            std::list<boost::shared_ptr<Asteroid> >& _asteroids;
            std::list<boost::shared_ptr<Bullet> >& _bullets;
            boost::shared_ptr<CollisionDetector> _collisionDetector;
    };
}

#endif
