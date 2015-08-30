#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Renderable.hpp>
#include <ScreenInfo.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using ::testing::ElementsAre;


struct VoidRenderable : public Renderable
{
    void render(const Coordinate& iCoordinate) {} 
};


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
        {}

        TestImageLoader _imageLoader;
        ScreenInfo _screenInfo;
        GameElements _gameElements;
};

TEST_F(GameElementsTest, ReturnsFalseWhenImageLoadFails)
{
    VoidRenderable voidRenderable;
    _imageLoader.loadSuccess = false;
    _imageLoader.renderable = &voidRenderable;
    EXPECT_FALSE(_gameElements.initialise());
}

TEST_F(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    TestRenderable shipImage;
    _imageLoader.renderable = &shipImage;
    _gameElements.initialise();
    _gameElements.render();
    EXPECT_THAT(shipImage.renderCalls, ElementsAre(Coordinate(320, 240)));

}
