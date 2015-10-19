#include <gmock/gmock.h>
#include <CollisionInteractions.hpp>
#include <CollisionDetector.hpp>
#include <Rectangle.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
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
                                 list<shared_ptr<Asteroid> >& iAsteroids,
                                 list<shared_ptr<Bullet> >& iBullets)
        : CollisionInteractions(iShip, iAsteroids, iBullets)
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
              _collisionInteractions(_ship, _asteroids, _bullets)
        {
            _ship->boundingBox = Rectangle(0,1,1,1);
            for (int i = 0; i < 3; ++i)
            {
                shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
                asteroid->boundingBox = Rectangle(i+1,1,1,1);
                _asteroids.push_back(asteroid);
            }
            shared_ptr<TestBullet> bullet = make_shared<TestBullet>();
            bullet->boundingBox = Rectangle(4,1,1,1);
            _bullets.push_back(bullet);
            _collisionInteractions.resetCollisionDetector(_collisionDetector);
        }

        shared_ptr<TestShip> _ship;
        list<shared_ptr<Asteroid> > _asteroids;
        list<shared_ptr<Bullet> > _bullets;
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

TEST_F(CollisionInteractionsTest, DelegatesCollisionUpdateToShipWhereDetected)
{
    _collisionDetector->colliding.push_back(pair<float, float>(0,1));
    _collisionInteractions.update();
    list<shared_ptr<Asteroid> >::iterator firstIt = _asteroids.begin();
    shared_ptr<TestAsteroid> firstAsteroid = dynamic_pointer_cast<TestAsteroid>(*firstIt);
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

    list<shared_ptr<Asteroid> >::iterator firstIt = _asteroids.begin();
    shared_ptr<TestAsteroid> firstAsteroid = dynamic_pointer_cast<TestAsteroid>(*firstIt);
    list<Asteroid*> firstCollideCalls = firstAsteroid->collideCalls;

    list<shared_ptr<Asteroid> >::iterator secondIt = firstIt;
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

    shared_ptr<Asteroid> asteroid = _asteroids.front();
    shared_ptr<TestAsteroid> testAsteroid = dynamic_pointer_cast<TestAsteroid>(asteroid);

    shared_ptr<Bullet> bullet = _bullets.front();
    shared_ptr<TestBullet> testBullet = dynamic_pointer_cast<TestBullet>(bullet);

    EXPECT_THAT(testAsteroid->bulletCollideCalls, ElementsAre(bullet.get()));
    EXPECT_THAT(testBullet->collideCalls, ElementsAre(asteroid.get()));
}
