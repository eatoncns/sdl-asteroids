#include <gmock/gmock.h>
#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Renderable.hpp>

using namespace pjm;

struct VoidRenderable : public Renderable
{ void render(const Coordinate& iCoordinate) {} };

class TestImageLoader : public ImageLoader
{
    public:
        TestImageLoader()
            : loadSuccess(true)
        {}

        Renderable* loadFromFile(const std::string& iFilePath)
        {
            if (loadSuccess)
            {
                return &_renderable;
            }
            return NULL;
        }

        bool loadSuccess;

    private:
        VoidRenderable _renderable;
    
};

TEST(GameElementsTest, ReturnsFalseWhenImageLoadFails)
{
    TestImageLoader imageLoader;
    imageLoader.loadSuccess = false;
    GameElements gameElements(imageLoader);
    EXPECT_FALSE(gameElements.initialise());
}
