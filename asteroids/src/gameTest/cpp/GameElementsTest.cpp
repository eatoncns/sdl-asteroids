#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
#include <TestCollisionInteractions.hpp>
#include <ShipAction.hpp>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>

using namespace pjm;
using std::list;
using boost::shared_ptr;
using boost::make_shared;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::NiceMock;

const unsigned int irrelevantTime = 3;

list<shared_ptr<TestAsteroid> > initTestAsteroids()
{
    list<shared_ptr<TestAsteroid> > asteroids;
    for (int i = 0 ; i < 5; ++i)
    {
        shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
        asteroids.push_back(asteroid);
    }
    return asteroids;
}

class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _ship(new TestShip()),
              _asteroids(initTestAsteroids()),
              _bullet(new NiceMock<TestBullet>()),
              _collisionInteractions(new TestCollisionInteractions()),
              _gameElements(_ship,
                            list<shared_ptr<Asteroid> >(_asteroids.begin(),
                                                        _asteroids.end()))
        {
            _gameElements.overrideCollisionInteractions(_collisionInteractions);
        }

        void shootBullet()
        {
            _ship->willShootBullet(_bullet);
            _gameElements.update(ShipAction().shooting(), irrelevantTime);
        }

        shared_ptr<TestShip> _ship;
        list<shared_ptr<TestAsteroid> > _asteroids;
        shared_ptr<NiceMock<TestBullet> > _bullet;
        shared_ptr<TestCollisionInteractions> _collisionInteractions;
        GameElements _gameElements;
};


TEST_F(GameElementsTest, CascadesRenderToShip)
{
    _gameElements.render();
    EXPECT_THAT(_ship->renderCalls, Eq(1));
}

TEST_F(GameElementsTest, CascadesRenderToAsteroids)
{
    _gameElements.render();
    BOOST_FOREACH(shared_ptr<TestAsteroid> asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->renderCalls, Eq(1));
    }
}

TEST_F(GameElementsTest, CascadesRenderToBullets)
{
    shootBullet();
    _gameElements.render();
    EXPECT_THAT(_bullet->renderCalls, Eq(1));
}

TEST_F(GameElementsTest, CascadesUpdateToAsteroids)
{
    _gameElements.update(ShipAction(), 3);
    _gameElements.update(ShipAction().accelerating(), 2);
    BOOST_FOREACH(shared_ptr<TestAsteroid> asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->updateCalls, ElementsAre(3, 2));
    }
}

TEST_F(GameElementsTest, CascadesUpdateToBullets)
{
    shootBullet();
    EXPECT_CALL(*_bullet, update(3));
    _gameElements.update(ShipAction(), 3);
}

TEST_F(GameElementsTest, CascadesUpdateToCollisionInteractions)
{
    _gameElements.update(ShipAction(), irrelevantTime);
    EXPECT_THAT(_collisionInteractions->updateCalls, Eq(1));
}

TEST_F(GameElementsTest, UpdateReturnsFalseOnShipExpiry)
{
    _ship->expired = true;
    EXPECT_THAT(_gameElements.update(ShipAction(), irrelevantTime), Eq(true));
}

TEST_F(GameElementsTest, RemovesExpiredAsteroidsAfterUpdate)
{
    _asteroids.front()->expired = true;
    _gameElements.update(ShipAction(), 3);
    _gameElements.update(ShipAction(), 2);
    EXPECT_THAT(_asteroids.front()->updateCalls, ElementsAre(3));
}

TEST_F(GameElementsTest, RemovesExpiredBulletsOnUpdate)
{
    EXPECT_CALL(*_bullet, update(3)).Times(1);
    shootBullet();
    _bullet->expired = true;
    _gameElements.update(ShipAction(), 3);
    _gameElements.update(ShipAction(), 3);
}
