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
using boost::shared_ptr;
using boost::make_shared;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::NiceMock;

struct TestableGameElements : public GameElements
{
    TestableGameElements(shared_ptr<Ship> iShip,
                         std::list<shared_ptr<TestAsteroid> > iAsteroids)
        : GameElements(iShip,
                       std::list<shared_ptr<Asteroid> >(iAsteroids.begin(), iAsteroids.end()))
    {}

    void addBullet(shared_ptr<Bullet> iBullet)
    {
        _bullets.push_back(iBullet);
    }

    void resetCollisionInteractions(CollisionInteractions* iCollisionInteractions)
    {
        _collisionInteractions.reset(iCollisionInteractions);
    }

    std::list<shared_ptr<Asteroid> >& getAsteroids()
    {
        return _asteroids;
    }

    std::list<shared_ptr<Bullet> >& getBullets()
    {
        return _bullets;
    }
};

std::list<shared_ptr<TestAsteroid> > initAsteroids()
{
    std::list<shared_ptr<TestAsteroid> > asteroids;
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
              _asteroids(initAsteroids()),
              _bullet(new NiceMock<TestBullet>()),
              _collisionInteractions(new TestCollisionInteractions()),
              _gameElements(_ship, _asteroids)
        {
            _gameElements.addBullet(_bullet);
            _gameElements.resetCollisionInteractions(_collisionInteractions);
        }

        shared_ptr<TestShip> _ship;
        std::list<shared_ptr<TestAsteroid> > _asteroids;
        shared_ptr<NiceMock<TestBullet> > _bullet;
        TestCollisionInteractions* _collisionInteractions;
        TestableGameElements _gameElements;
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
    EXPECT_CALL(*_bullet, update(3));
    _gameElements.update(ShipAction(), 3);
}

TEST_F(GameElementsTest, CascadesUpdateToCollisionInteractions)
{
    _gameElements.update(ShipAction(), 3);
    EXPECT_THAT(_collisionInteractions->updateCalls, Eq(1));
}

TEST_F(GameElementsTest, UpdateReturnsFalseOnShipExpiry)
{
    _ship->expired = true;
    EXPECT_THAT(_gameElements.update(ShipAction(), 2), Eq(true));
}

TEST_F(GameElementsTest, RemovesExpiredAsteroidsOnUpdate)
{
    _asteroids.front()->expired = true;
    _gameElements.update(ShipAction(), 3);
    EXPECT_THAT(_gameElements.getAsteroids().size(), Eq(4));
}

TEST_F(GameElementsTest, RemovesExpiredBulletsOnUpdate)
{
    _bullet->expired = true;
    _gameElements.update(ShipAction(), 3);
    EXPECT_THAT(_gameElements.getBullets().empty(), Eq(true));
}

TEST_F(GameElementsTest, IgnoresUninitialisedBulletFromUpdate)
{
    _gameElements.update(ShipAction(), 3);
    EXPECT_THAT(_gameElements.getBullets().size(), Eq(1));
}

TEST_F(GameElementsTest, AddsInitialisedBulletFromUpdate)
{
    _ship->bullet = _bullet;
    _gameElements.update(ShipAction(), 3);
    EXPECT_THAT(_gameElements.getBullets().size(), Eq(2));
}
