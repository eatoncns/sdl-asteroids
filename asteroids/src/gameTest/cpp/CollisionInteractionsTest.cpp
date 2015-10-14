#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <algorithm>

using namespace pjm;
using namespace boost;
using std::pair;
using std::make_pair;
using std::list;
using ::testing::Eq;
using ::testing::Contains;
using ::testing::ElementsAre;
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

struct TestableCollisionInteractions : public CollisionInteractions
{
    TestableCollisionInteractions(shared_ptr<Ship> iShip,
                                 list<shared_ptr<Asteroid> >& iAsteroids)
        : CollisionInteractions(iShip, iAsteroids)
    {}

    void resetCollisionDetector(CollisionDetector* iCollisionDetector)
    {
        _collisionDetector.reset(iCollisionDetector);
    }
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
                shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
                asteroid->boundingBox = Rectangle(i+1,1,1,1);
                _asteroids.push_back(asteroid);
            }
            _collisionInteractions.resetCollisionDetector(_collisionDetector);
        }

        shared_ptr<TestShip> _ship;
        list<shared_ptr<Asteroid> > _asteroids;
        FakeCollisionDetector* _collisionDetector;
        TestableCollisionInteractions _collisionInteractions;
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

TEST_F(CollisionInteractionsTest, DelegatesCollisionUpdateToAsteroidsWhereDetected)
{
    _collisionDetector->colliding.push_back(pair<float, float>(1,2));
    _collisionInteractions.update();

    list<shared_ptr<Asteroid> >::iterator firstIt = _asteroids.begin();
    shared_ptr<TestAsteroid> firstAsteroid = dynamic_pointer_cast<TestAsteroid>(*firstIt);
    list<Asteroid*> firstCollideCalls = firstAsteroid->collideCalls;

    list<shared_ptr<Asteroid> >::iterator secondIt = firstIt;
    secondIt++;
    Asteroid* secondAsteroid = secondIt->get();

    EXPECT_THAT(firstCollideCalls, ElementsAre(secondAsteroid));
}
