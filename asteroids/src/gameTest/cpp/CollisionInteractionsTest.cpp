#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <boost/foreach.hpp>

using namespace pjm;
using namespace std;
using ::testing::Eq;
using ::testing::Contains;
using ::testing::NiceMock;

struct FakeCollisionDetector : public CollisionDetector
{
    FakeCollisionDetector()
        : collisionResult(false)
    {}

    bool areColliding(const Rectangle& iA, const Rectangle& iB) const
    {
        calls.push_back(make_pair(iA.x, iB.x));
        return collisionResult;
    }

    bool collisionResult;
    mutable list<pair<float, float> > calls;
};

class CollisionInteractionsTest : public ::testing::Test
{
    protected:
        CollisionInteractionsTest()
            : _ship(new TestShip()),
              _collisionDetector(new FakeCollisionDetector()), // deleted by _collisionInteractions
              _collisionInteractions(_ship, _asteroids)
        {
            _ship->boundingBox = Rectangle(0,1,1,1); 
            for (int i = 0; i < 3; ++i)
            {
                TestAsteroid* asteroid = new TestAsteroid();
                asteroid->boundingBox = Rectangle(i+1,1,1,1);
                _asteroids.push_back(asteroid);
            }
            _collisionInteractions._collisionDetector.reset(_collisionDetector);
        }

        ~CollisionInteractionsTest()
        {
            delete _ship;
            BOOST_FOREACH(Asteroid* asteroid, _asteroids)
            {
                delete asteroid;
            }
        }
              
        TestShip* _ship;
        list<Asteroid*> _asteroids;
        FakeCollisionDetector* _collisionDetector;
        CollisionInteractions _collisionInteractions;
};

TEST_F(CollisionInteractionsTest, ChecksShipCollisionWithAllAsteroids)
{
    _collisionInteractions.update();
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 1)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 2)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 3)));
}

TEST_F(CollisionInteractionsTest, ReturnsFalseWhenNoShipCollisionOccurs)
{
    EXPECT_THAT(_collisionInteractions.update(), Eq(false)); 
}

TEST_F(CollisionInteractionsTest, ReturnsTrueWhenShipCollisionOccurs)
{
    _collisionDetector->collisionResult = true;
    EXPECT_THAT(_collisionInteractions.update(), Eq(true));
}
