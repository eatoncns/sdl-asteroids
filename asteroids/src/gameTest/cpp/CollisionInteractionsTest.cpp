#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

using namespace pjm;
using namespace std;
using ::testing::Eq;
using ::testing::Contains;
using ::testing::NiceMock;

struct FakeCollisionDetector : public CollisionDetector
{
    bool areColliding(const Rectangle& iA, const Rectangle& iB) const
    {
        pair<float, float> inputPair = make_pair(iA.x, iB.x);
        calls.push_back(inputPair);
        pair_list::const_iterator it = find(colliding.begin(), colliding.end(), inputPair);
        return (it != colliding.end());
    }
    
    typedef list<pair<float, float> > pair_list;
    pair_list colliding;
    mutable pair_list calls;
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
    _collisionDetector->colliding.push_back(pair<float, float>(0,2));
    EXPECT_THAT(_collisionInteractions.update(), Eq(true));
}

TEST_F(CollisionInteractionsTest, ChecksAsteroidCollisionsWhenNoShipCollision)
{
    _collisionInteractions.update();
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(1,2)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(1,3)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(2,3)));
}
