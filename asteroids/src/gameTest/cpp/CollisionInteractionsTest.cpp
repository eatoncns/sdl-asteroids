#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <boost/foreach.hpp>

using namespace pjm;
using ::testing::NiceMock;

struct FakeCollisionDetector : public CollisionDetector
{
    bool areColliding(const Rectangle& iA, const Rectangle& iB)
    {
        calls.push_back(std::make_pair(iA.x, iB.x));
    }

    std::list<std::pair<float, float> > calls;
};

class CollisionInteractionsTest : public ::testing::Test
{
    protected:
        CollisionInteractionsTest()
            : _ship(new TestShip()),
              _collisionInteractions(_ship, _asteroids)
        {
            //_ship->boundingBox = Rectangle(1,1,1,1); 
            for (int i = 0; i < 3; ++i)
            {
                _asteroids.push_back(new TestAsteroid());
                //_asteroids[i]->boundingBox = Rectangle(i,1,1,1);
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
        FakeCollisionDetector _collisionDetector;
        CollisionInteractions _collisionInteractions;
};

TEST_F(CollisionInteractionsTest, ChecksShipCollisionWithAllAsteroids)
{
}
