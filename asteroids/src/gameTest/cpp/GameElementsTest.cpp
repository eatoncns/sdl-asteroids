#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Renderable.hpp>
#include <ScreenInfo.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using ::testing::ElementsAre;


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
};

TEST_F(GameElementsTest, ReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, ReturnsTrueWhenInitialisationSucceeds)
{
    EXPECT_TRUE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    _gameElements.initialise();
    _gameElements.render();
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(Coordinate(320, 240)));
}
