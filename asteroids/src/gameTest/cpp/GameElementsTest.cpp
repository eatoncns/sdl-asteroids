#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
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

    void resetCollisionInteractions(CollisionInteractions* iCollisionInteractions)
    {
        _collisionInteractions.reset(iCollisionInteractions);
    }
};

class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _ship(new TestShip()),
              _collisionInteractions(new TestCollisionInteractions()),
              _gameElements(_ship)
        {
            for (int i = 0 ; i < 5; ++i)
            {
                shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
                _asteroids.push_back(asteroid);
                _gameElements.addAsteroid(asteroid);
            }
            _gameElements.resetCollisionInteractions(_collisionInteractions);
        }

        shared_ptr<TestShip> _ship;
        std::list<shared_ptr<TestAsteroid> > _asteroids;
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

TEST_F(GameElementsTest, ConvertsUpKeyToShipAccelerate)
{
    _gameElements.update(keyboard::UP, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE, 5)));
}

TEST_F(GameElementsTest, ConvertsNoneKeyToShipNone)
{
    _gameElements.update(keyboard::NONE, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::NONE, 5)));
}

TEST_F(GameElementsTest, ConvertsLeftKeyToShipTurnLeft)
{
    _gameElements.update(keyboard::LEFT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::TURN_LEFT, 5)));
}

TEST_F(GameElementsTest, ConvertsRightKeyToShipTurnRight)
{
    _gameElements.update(keyboard::RIGHT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::TURN_RIGHT, 5)));
}

TEST_F(GameElementsTest, ConvertsUpLeftToAccelerateLeft)
{
    _gameElements.update(keyboard::UP_LEFT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE_LEFT, 5))); 
}

TEST_F(GameElementsTest, ConvertsUpRightToAccelerateRight)
{
    _gameElements.update(keyboard::UP_RIGHT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE_RIGHT, 5))); 
}

TEST_F(GameElementsTest, CascadesUpdateToAsteroids)
{
    _gameElements.update(keyboard::NONE, 3);
    _gameElements.update(keyboard::UP, 2);
    BOOST_FOREACH(shared_ptr<TestAsteroid> asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->updateCalls, ElementsAre(3, 2));
    }
}

TEST_F(GameElementsTest, CascadesUpdateToCollisionInteractions)
{
    _gameElements.update(keyboard::NONE, 3);
    EXPECT_THAT(_collisionInteractions->updateCalls, Eq(1));
}

TEST_F(GameElementsTest, UpdateReturnsFalseOnShipCollision)
{
    _collisionInteractions->shipCollision = true;
    EXPECT_THAT(_gameElements.update(keyboard::NONE, 2), Eq(true));
}
