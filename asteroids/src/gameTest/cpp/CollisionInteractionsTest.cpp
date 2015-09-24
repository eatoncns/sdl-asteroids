/*
#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>

class CollisionInteractionsTest : public ::testing:Test
{
    protected:
        CollisionInteractionsTest()
        {
            _ship = new TestShip();
            for (int i = 0; i < 3; ++i)
            {
                _asteroids.push_back(new TestAsteroid());
            }
            _collisionInteractions(_ship, _asteroids);
        }
              

        Ship* _ship;
        std::list<Asteroid*> _asteroids;
        CollisionInteractions _collisionInteractions;
};
*/
