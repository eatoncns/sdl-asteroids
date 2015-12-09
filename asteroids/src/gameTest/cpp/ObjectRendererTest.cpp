#include <gmock/gmock.h>
#include <ObjectRenderer.hpp>
#include <TestImageLoader.hpp>
#include <TestRenderable.hpp>
#include <Rectangle.hpp>
#include <boost/math/special_functions/round.hpp>

using namespace pjm;
using namespace boost::math;
using boost::shared_ptr;
using ::testing::Eq;
using ::testing::Pair;
using ::testing::_;

class ObjectRendererTest : public ::testing::Test
{
    protected:
        ObjectRendererTest()
          : renderable(new TestRenderable())
        {
            imageLoader.renderable = renderable;
        }

        ObjectRenderer renderer;
        TestImageLoader imageLoader;
        shared_ptr<TestRenderable> renderable;
};

TEST_F(ObjectRendererTest, InitialiseReturnsFalseWhenImageLoadFails)
{
    imageLoader.loadSuccess = false;
    EXPECT_THAT(renderer.initialise(imageLoader, "filePath"), Eq(false));
}

TEST_F(ObjectRendererTest, InitialiseReturnsTrueWhenImageLoadSucceeds)
{
    EXPECT_THAT(renderer.initialise(imageLoader, "filePath"), Eq(true));
}

TEST_F(ObjectRendererTest, RendersImageAtGivenLocation)
{
    renderer.initialise(imageLoader, "filePath");
    renderer.renderAt(Vector(4,4), 25.0);
    ASSERT_THAT(renderable->renderCalls.empty(), Eq(false));
    EXPECT_THAT(renderable->renderCalls.front(), Pair(Vector(4,4),_));
}

TEST_F(ObjectRendererTest, ReturnsScaledRectangleBoundingBoxForImage)
{
    renderer.initialise(imageLoader, "filePath");
    int testLength = 53;
    renderable->w = testLength;
    renderable->h = testLength;
    Vector location(100, 100);
    Rectangle boundingBox = renderer.getBoundingBox(location);
    float ratioLength = testLength*ObjectRenderer::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(location.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(location.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}
