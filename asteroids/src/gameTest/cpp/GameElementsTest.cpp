#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Renderable.hpp>
#include <ScreenInfo.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using ::testing::ElementsAre;

struct VoidRenderable : public Renderable
{ void render(const Coordinate& iCoordinate) {} };

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

TEST(GameElementsTest, ReturnsFalseWhenImageLoadFails)
{
    VoidRenderable voidRenderable;
    TestImageLoader imageLoader;
    imageLoader.loadSuccess = false;
    imageLoader.renderable = &voidRenderable;
    ScreenInfo screenInfo("test", 640, 480);
    GameElements gameElements(imageLoader, screenInfo);
    EXPECT_FALSE(gameElements.initialise());
}

TEST(GameElementsTest, InitialisesShipInCentreOfScreen)
{
    TestRenderable shipImage;
    TestImageLoader imageLoader;
    imageLoader.renderable = &shipImage;
    ScreenInfo screenInfo("test", 640, 480);
    GameElements gameElements(imageLoader, screenInfo);
    gameElements.initialise();
    gameElements.render();
    EXPECT_THAT(shipImage.renderCalls, ElementsAre(Coordinate(320, 240)));

}
