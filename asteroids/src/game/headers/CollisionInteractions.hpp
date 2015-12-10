#ifndef _PJM_COLLISIONINTERACTIONS_HPP_
#define _PJM_COLLISIONINTERACTIONS_HPP_

#include <CollisionDetector.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;
    class FixedSpeedBullet;

    class CollisionInteractions
    {
        public:
            CollisionInteractions(boost::shared_ptr<Ship> iShip,
                                  std::list<boost::shared_ptr<Asteroid> >& iAsteroids,
                                  std::list<boost::shared_ptr<FixedSpeedBullet> >& iBullets);

            virtual void update();

            virtual ~CollisionInteractions() {}

            void overrideCollisionDetector(boost::shared_ptr<CollisionDetector> iCollisionDetector);

        private:
            void handleShipCollision();
            void handleAsteroidCollisions();
            void handleBulletCollisions();

            boost::shared_ptr<Ship> _ship;
            std::list<boost::shared_ptr<Asteroid> >& _asteroids;
            std::list<boost::shared_ptr<FixedSpeedBullet> >& _bullets;
            boost::shared_ptr<CollisionDetector> _collisionDetector;
    };
}

#endif
