#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <KeyPress.hpp>
#include <CollisionInteractions.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

namespace pjm
{
    class Ship;
    class Asteroid;

    class GameElements
    {
        public:
            GameElements(boost::shared_ptr<Ship> iShip,
                         std::list<boost::shared_ptr<Asteroid> > iAsteroids);

            bool update(keyboard::KeyPress iKeyPress, unsigned int iTimeElapsed);

            void render();
             
        protected:
            boost::shared_ptr<Ship> _ship;
            std::list<boost::shared_ptr<Asteroid> > _asteroids;
            boost::scoped_ptr<CollisionInteractions> _collisionInteractions;
    };
}

#endif
