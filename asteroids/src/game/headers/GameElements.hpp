#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ShipAction.hpp>
#include <CollisionInteractions.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    struct ShipAction;
    class Asteroid;
    class Bullet;

    class GameElements
    {
        public:
            GameElements(boost::shared_ptr<Ship> iShip,
                         std::list<boost::shared_ptr<Asteroid> > iAsteroids);

            bool update(const ShipAction& iAction, unsigned int iTimeElapsed);

            void render();

            void overrideCollisionInteractions(
                boost::shared_ptr<CollisionInteractions> iCollisionInteractions);

        private:
            boost::shared_ptr<Ship> _ship;
            std::list<boost::shared_ptr<Asteroid> > _asteroids;
            std::list<boost::shared_ptr<Bullet> > _bullets;
            boost::shared_ptr<CollisionInteractions> _collisionInteractions;

            void updateShip(const ShipAction& iAction, unsigned int iTimeElapsed);
            void updateAsteroids(unsigned int iTimeElapsed);
            void updateBullets(unsigned int iTimeElapsed);
            void handleCollisions();
            void removeExpiredBullets();
            void removeExpiredAsteroids();
    };
}

#endif
