#ifndef _PJM_COLLISIONINTERACTIONS_HPP_
#define _PJM_COLLISIONINTERACTIONS_HPP_

#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;

    class CollisionInteractions
    {
        public:
            CollisionInteractions(Ship* iShip, std::list<Asteroid*>& iAsteroids)
                : _ship(iShip), _asteroids(iAsteroids)
            {}

        private:
            Ship* _ship;
            std::list<Asteroid*>& _asteroids;
    };
}

#endif
