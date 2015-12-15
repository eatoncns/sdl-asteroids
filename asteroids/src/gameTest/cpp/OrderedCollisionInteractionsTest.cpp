#include <gmock/gmock.h>
#include <OrderedCollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
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

namespace
{
    shared_ptr<TestShip> initTestShip()
    {
        shared_ptr<TestShip> ship = make_shared<TestShip>();
        ship->boundingBox = Rectangle(0,1,1,1);
        return ship;
    }

    list<shared_ptr<TestAsteroid> > initTestAsteroids()
    {
        list<shared_ptr<TestAsteroid> > asteroids;
        for (int i = 0; i < 3; ++i)
        {
            shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
            asteroid->boundingBox = Rectangle(i+1,1,1,1);
            asteroids.push_back(asteroid);
        }
        return asteroids;
    }

    list<shared_ptr<TestBullet> > initTestBullets()
    {
        list<shared_ptr<TestBullet> > bullets;
        shared_ptr<TestBullet> bullet = make_shared<TestBullet>();
        bullet->boundingBox = Rectangle(4,1,1,1);
        bullets.push_back(bullet);
        return bullets;
    }
}

class CollisionInteractionsTest : public ::testing::Test
{
    protected:
        CollisionInteractionsTest()
            : _ship(initTestShip()),
              _testAsteroids(initTestAsteroids()),
              _testBullets(initTestBullets()),
              _asteroids(_testAsteroids.begin(), _testAsteroids.end()),
              _bullets(_testBullets.begin(), _testBullets.end()),
              _collisionDetector(new FakeCollisionDetector()),
              _collisionInteractions(_ship, _asteroids, _bullets)
        {
            _collisionInteractions.overrideCollisionDetector(_collisionDetector);
        }

        shared_ptr<TestShip> _ship;
        list<shared_ptr<TestAsteroid> > _testAsteroids;
        list<shared_ptr<TestBullet> > _testBullets;
        // As target class takes references to lists owned by GameElements
        // here we take copies of the test type lists to pass in
        list<shared_ptr<Asteroid> > _asteroids;
        list<shared_ptr<Bullet> > _bullets;
        shared_ptr<FakeCollisionDetector> _collisionDetector;
        OrderedCollisionInteractions _collisionInteractions;
};

TEST_F(CollisionInteractionsTest, ChecksShipCollisionWithAllAsteroids)
{
    _collisionInteractions.update();
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 1)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 2)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(0, 3)));
}

TEST_F(CollisionInteractionsTest, DelegatesCollisionUpdateToShipWhereDetected)
{
    _collisionDetector->colliding.push_back(pair<float, float>(0,1));
    _collisionInteractions.update();
    shared_ptr<TestAsteroid> firstAsteroid = _testAsteroids.front();
    EXPECT_THAT(_ship->collideCalls, ElementsAre(firstAsteroid.get()));
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

    list<shared_ptr<TestAsteroid> >::iterator firstIt = _testAsteroids.begin();
    shared_ptr<TestAsteroid> firstAsteroid = *firstIt;
    list<Asteroid*> firstCollideCalls = firstAsteroid->collideCalls;

    list<shared_ptr<TestAsteroid> >::iterator secondIt = firstIt;
    secondIt++;
    Asteroid* secondAsteroid = secondIt->get();

    EXPECT_THAT(firstCollideCalls, ElementsAre(secondAsteroid));
}

TEST_F(CollisionInteractionsTest, ChecksBulletCollisionWhenNoShipCollision)
{
    _collisionInteractions.update();
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(4, 1)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(4, 2)));
    EXPECT_THAT(_collisionDetector->calls, Contains(make_pair(4, 3)));
}

TEST_F(CollisionInteractionsTest, DelegatesAsteroidBulletCollisionToBothParties)
{
    _collisionDetector->colliding.push_back(pair<float, float>(4,1));
    _collisionInteractions.update();

    shared_ptr<TestAsteroid> asteroid = _testAsteroids.front();
    shared_ptr<TestBullet> bullet = _testBullets.front();

    EXPECT_THAT(asteroid->bulletCollideCalls, ElementsAre(bullet.get()));
    EXPECT_THAT(bullet->collideCalls, ElementsAre(asteroid.get()));
}
