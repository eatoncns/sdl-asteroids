#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ScreenInfo.hpp>
#include <TestImageLoader.hpp>
#include <TestRandomGenerator.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestLocationGenerator.hpp>
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
};

class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _ship(new TestShip()),
              _gameElements(_ship)
        {
            for (int i = 0 ; i < 5; ++i)
            {
                shared_ptr<TestAsteroid> asteroid = make_shared<TestAsteroid>();
                _asteroids.push_back(asteroid);
                _gameElements.addAsteroid(asteroid);
            }
        }

        shared_ptr<TestShip> _ship;
        std::list<shared_ptr<TestAsteroid> > _asteroids;
        TestableGameElements _gameElements;
};

/*TEST_F(GameElementsTest, InitReturnsFalseWhenAsteroidInitFails)
{
    _asteroids[0]->initialiseSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitReturnsTrueWhenInitialisationSucceeds)
{
    EXPECT_TRUE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesFixedNumberOfAsteroids)
{
    _gameElements.initialise();
    EXPECT_THAT(_asteroidCounter, Eq(GameElements::NUM_ASTEROIDS));
}

TEST_F(GameElementsTest, InitialisesAsteroidsAtRandomLocation)
{
    _gameElements.initialise();
    BOOST_FOREACH(TestAsteroid* asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->initialiseCalls, 
                    ElementsAre(Vector(TestLocationGenerator::x, TestLocationGenerator::y)));
    }
}*/

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
