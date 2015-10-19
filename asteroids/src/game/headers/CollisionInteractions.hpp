#ifndef _PJM_COLLISIONINTERACTIONS_HPP_
#define _PJM_COLLISIONINTERACTIONS_HPP_

#include <CollisionDetector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;
    class Bullet;

    class CollisionInteractions
    {
        public:
            CollisionInteractions(boost::shared_ptr<Ship> iShip,
                                  std::list<boost::shared_ptr<Asteroid> >& iAsteroids,
                                  std::list<boost::shared_ptr<Bullet> >& iBullets);

            virtual ~CollisionInteractions() {}

            virtual void update();

        protected:
            boost::scoped_ptr<CollisionDetector> _collisionDetector;

        private:
            void handleShipCollision();
            void handleAsteroidCollisions();
            void handleBulletCollisions();

            boost::shared_ptr<Ship> _ship;
            std::list<boost::shared_ptr<Asteroid> >& _asteroids;
            std::list<boost::shared_ptr<Bullet> >& _bullets;
    };
}

#endif
