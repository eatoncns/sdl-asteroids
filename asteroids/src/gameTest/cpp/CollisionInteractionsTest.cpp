#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <boost/foreach.hpp>

using namespace pjm;

class CollisionInteractionsTest : public ::testing::Test
{
    protected:
        CollisionInteractionsTest()
            : _ship(new TestShip()),
              _collisionInteractions(_ship, _asteroids)
        {
            for (int i = 0; i < 3; ++i)
            {
                _asteroids.push_back(new TestAsteroid());
            }
        }

        ~CollisionInteractionsTest()
        {
            delete _ship;
            BOOST_FOREACH(Asteroid* asteroid, _asteroids)
            {
                delete asteroid;
            }
        }
              
        Ship* _ship;
        std::list<Asteroid*> _asteroids;
        CollisionInteractions _collisionInteractions;
};

TEST_F(CollisionInteractionsTest, InterfaceCompiles)
{

}
