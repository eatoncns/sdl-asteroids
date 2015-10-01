#ifndef _PJM_COLLISIONINTERACTIONS_HPP_
#define _PJM_COLLISIONINTERACTIONS_HPP_

#include <CollisionDetector.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;

    class CollisionInteractions
    {
        public:
            CollisionInteractions(Ship* iShip, std::list<Asteroid*>& iAsteroids);

            virtual ~CollisionInteractions() {}

            virtual bool update();

            boost::scoped_ptr<CollisionDetector> _collisionDetector;

        private:
            bool shipIsColliding();
            void handleAsteroidCollisions();

            Ship* _ship;
            std::list<Asteroid*>& _asteroids;
    };
}

#endif
