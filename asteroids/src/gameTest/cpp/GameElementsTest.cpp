#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Renderable.hpp>
#include <ScreenInfo.hpp>
#include <TestRenderable.hpp>
#include <Ship.hpp>
#include <KeyPress.hpp>
#include <utility>

using namespace pjm;
using ::testing::ElementsAre;
using ::testing::Eq;


struct TestImageLoader : public ImageLoader
{
    TestImageLoader()
        : loadSuccess(true),
          renderable(NULL)
    {}

    Renderable* loadFromFile(const std::string& iFilePath)
    {
        if (loadSuccess)
        {
            return renderable;
        }
        return NULL;
    }

    bool loadSuccess;
    Renderable* renderable;
};


struct TestShip : public Ship
{
    TestShip()
        : Ship(Vector(0,0), renderable),
          renderCalls(0)
    {}

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
    TestRenderable renderable;
};


class GameElementsTest : public ::testing::Test
{
    protected:
        GameElementsTest()
            : _screenInfo("test", 640, 480),
              _gameElements(_imageLoader, _screenInfo)
        {
            _imageLoader.renderable = &_shipImage;
        }

        TestImageLoader _imageLoader;
        ScreenInfo _screenInfo;
        GameElements _gameElements;
        TestRenderable _shipImage;
        TestShip _ship;
};

TEST_F(GameElementsTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitReturnsTrueWhenInitialisationSucceeds)
{
    EXPECT_TRUE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    _gameElements.initialise();
    _gameElements.render();
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(Vector(320, 240)));
}

TEST_F(GameElementsTest, CascadesRenderToShip)
{
    _gameElements._ship = &_ship;
    _gameElements.render();
    _gameElements._ship = NULL;
    EXPECT_THAT(_ship.renderCalls, Eq(1));
}

TEST_F(GameElementsTest, ConvertsUpKeyToShipAccelerate)
{
    _gameElements._ship = &_ship;
    _gameElements.update(keyboard::UP, 5);
    _gameElements._ship = NULL;
    EXPECT_THAT(_ship.updateCalls, ElementsAre(std::make_pair(Ship::ACCELERATE, 5)));
}

TEST_F(GameElementsTest, ConvertsNoneKeyToShipNone)
{
    _gameElements._ship = &_ship;
    _gameElements.update(keyboard::NONE, 5);
    _gameElements._ship = NULL;
    EXPECT_THAT(_ship.updateCalls, ElementsAre(std::make_pair(Ship::NONE, 5)));
}
