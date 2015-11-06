#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
#include <TestCollisionInteractions.hpp>
#include <KeyPress.hpp>
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
    TestableGameElements(shared_ptr<Ship> iShip)
        : GameElements(iShip, std::list<shared_ptr<Asteroid> >())
    {}

    void addAsteroid(shared_ptr<Asteroid> iAsteroid)
    {
        _asteroids.push_back(iAsteroid);
    }

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

class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _ship(new TestShip()),
              _bullet(new TestBullet()),
              _collisionInteractions(new TestCollisionInteractions()),
              _gameElements(_ship)
        {
            for (int i = 0 ; i < 5; ++i)
            {
                shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
                _asteroids.push_back(asteroid);
                _gameElements.addAsteroid(asteroid);
            }
            _gameElements.addBullet(_bullet);
            _gameElements.resetCollisionInteractions(_collisionInteractions);
        }

        shared_ptr<TestShip> _ship;
        std::list<shared_ptr<TestAsteroid> > _asteroids;
        shared_ptr<TestBullet> _bullet;
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

TEST_F(GameElementsTest, CascadesUpdateToAsteroids)
{
    _gameElements.update(ShipAction(), 3);
    ShipAction accelerateAction; accelerateAction.accelerate = true;
    _gameElements.update(accelerateAction, 2);
    BOOST_FOREACH(shared_ptr<TestAsteroid> asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->updateCalls, ElementsAre(3, 2));
    }
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
