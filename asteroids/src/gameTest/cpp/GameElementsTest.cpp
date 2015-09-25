#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ScreenInfo.hpp>
#include <TestImageLoader.hpp>
#include <TestRandomGenerator.hpp>
#include <TestShip.hpp>
#include <TestAsteroid.hpp>
#include <TestLocationGenerator.hpp>
#include <KeyPress.hpp>
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/foreach.hpp>

using namespace pjm;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::NiceMock;


class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _screenInfo("test", 640, 480),
              _gameElements(_imageLoader, _screenInfo, _random),
              _ship(new TestShip()), // deleted by gameElements
              _asteroidCounter(0)
        {
            _gameElements._shipCreator = boost::bind(&GameElementsTest::getShip, this, _1, _2);
            _gameElements._asteroidCreator = boost::bind(&GameElementsTest::getAsteroid, this, _1, _2, _3);
            for (int i = 0 ; i < GameElements::NUM_ASTEROIDS; ++i)
            {
                // deleted by gameElements
                _asteroids.push_back(new TestAsteroid());
            }
            _gameElements._locationGenerator.reset(new TestLocationGenerator());
        }

        Ship* getShip(ImageLoader&, ScreenWrapper&)
        {
            return _ship;
        }

        Asteroid* getAsteroid(ImageLoader&, ScreenWrapper&, RandomGenerator&)
        {
            Asteroid* asteroid = _asteroids[_asteroidCounter];
            ++_asteroidCounter;
            return asteroid;
        }

        ScreenInfo _screenInfo;
        TestImageLoader _imageLoader;
        TestRandomGenerator _random;
        GameElements _gameElements;
        TestShip* _ship;
        std::vector<TestAsteroid*> _asteroids;
        int _asteroidCounter;
};

TEST_F(GameElementsTest, InitReturnsFalseWhenShipInitFails)
{
    _ship->initialiseSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitReturnsFalseWhenAsteroidInitFails)
{
    _asteroids[0]->initialiseSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitReturnsTrueWhenInitialisationSucceeds)
{
    EXPECT_TRUE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    _gameElements.initialise();
    EXPECT_THAT(_ship->initialiseCalls, 
                ElementsAre(Vector(_screenInfo.width/2, _screenInfo.height/2)));
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
}

TEST_F(GameElementsTest, CascadesRenderToShip)
{
    _gameElements.initialise();
    _gameElements.render();
    EXPECT_THAT(_ship->renderCalls, Eq(1));
}

TEST_F(GameElementsTest, CascadesRenderToAsteroids)
{
    _gameElements.initialise();
    _gameElements.render();
    BOOST_FOREACH(TestAsteroid* asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->renderCalls, Eq(1));
    }
}

TEST_F(GameElementsTest, ConvertsUpKeyToShipAccelerate)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::UP, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE, 5)));
}

TEST_F(GameElementsTest, ConvertsNoneKeyToShipNone)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::NONE, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::NONE, 5)));
}

TEST_F(GameElementsTest, ConvertsLeftKeyToShipTurnLeft)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::LEFT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::TURN_LEFT, 5)));
}

TEST_F(GameElementsTest, ConvertsRightKeyToShipTurnRight)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::RIGHT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::TURN_RIGHT, 5)));
}

TEST_F(GameElementsTest, ConvertsUpLeftToAccelerateLeft)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::UP_LEFT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE_LEFT, 5))); 
}

TEST_F(GameElementsTest, ConvertsUpRightToAccelerateRight)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::UP_RIGHT, 5);
    EXPECT_THAT(_ship->updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE_RIGHT, 5))); 
}

TEST_F(GameElementsTest, CascadesUpdateToAsteroids)
{
    _gameElements.initialise();
    _gameElements.update(keyboard::NONE, 3);
    _gameElements.update(keyboard::UP, 2);
    BOOST_FOREACH(TestAsteroid* asteroid, _asteroids)
    {
        EXPECT_THAT(asteroid->updateCalls, ElementsAre(3, 2));
    }
}
