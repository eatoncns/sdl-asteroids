#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ScreenInfo.hpp>
#include <ScreenWrapper.hpp>
#include <TestImageLoader.hpp>
#include <TestRenderable.hpp>
#include <Ship.hpp>
#include <KeyPress.hpp>
#include <utility>
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>

using namespace pjm;
using ::testing::ElementsAre;
using ::testing::Eq;

struct TestShip : public Ship
{
    TestShip(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper)
        : Ship(iImageLoader, iScreenWrapper),
          renderCalls(0),
          initialiseSuccess(true)
    {}

    bool initialise(const Vector& iInitialLocation)
    {
        initialiseCalls.push_back(iInitialLocation);
        return initialiseSuccess;
    }

    void update(const Action iAction, unsigned int iTimeElapsed)
    {
        updateCalls.push_back(std::make_pair(iAction, iTimeElapsed));
    }

    void render()
    {
        ++renderCalls;
    }

    int renderCalls;
    std::list<std::pair<Action, unsigned int> > updateCalls;
    std::list<Vector> initialiseCalls;
    bool initialiseSuccess;
};


class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _screenInfo("test", 640, 480),
              _screenWrapper(Vector(640, 480)),
              _gameElements(_imageLoader, _screenInfo),
              _ship(new TestShip(_imageLoader, _screenWrapper)) // deleted by gameElements
        {
            _gameElements._shipCreator = boost::bind(&GameElementsTest::getShip, this, _1);
        }

        Ship* getShip(ImageLoader&)
        {
            return _ship;
        }

        ScreenInfo _screenInfo;
        ScreenWrapper _screenWrapper;
        TestImageLoader _imageLoader;
        GameElements _gameElements;
        TestShip* _ship;
};

TEST_F(GameElementsTest, InitReturnsFalseWhenShipInitFails)
{
    _ship->initialiseSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitReturnsTrueWhenInitialisationSucceeds)
{
    EXPECT_TRUE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    _gameElements.initialise();
    EXPECT_THAT(_ship->initialiseCalls, ElementsAre(Vector(320, 240)));
}

TEST_F(GameElementsTest, CascadesRenderToShip)
{
    _gameElements.initialise();
    _gameElements.render();
    EXPECT_THAT(_ship->renderCalls, Eq(1));
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
