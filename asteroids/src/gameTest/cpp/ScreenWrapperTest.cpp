#include <gmock/gmock.h>
#include <ScreenWrapper.hpp>
#include <Vector.hpp>

using namespace pjm;
using ::testing::Eq;

class ScreenWrapperTest : public ::testing::Test
{
    protected:
        ScreenWrapperTest()
            : bounds(200, 200),
              timeElapsed(1),
              distanceMoved(0.5),
              screenWrapper(bounds)
        {}

        Vector bounds;
        unsigned int timeElapsed;
        float distanceMoved;
        ScreenWrapper screenWrapper;
};

TEST_F(ScreenWrapperTest, WrapsTopToBottom)
{
    Vector location(bounds.x/2, -distanceMoved);
    Vector velocity(0, -distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2, bounds.y - distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsTopToLeft)
{
    Vector location(bounds.x/2 + distanceMoved, -distanceMoved);
    Vector velocity(distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(distanceMoved, bounds.y/2 - distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsTopToRight)
{
    Vector location(bounds.x/2 - distanceMoved, -distanceMoved);
    Vector velocity(-distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x - distanceMoved, bounds.y/2 - distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsLeftToRight)
{
    Vector location(-distanceMoved, bounds.y/2);
    Vector velocity(-distanceMoved/timeElapsed, 0);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x - distanceMoved, bounds.y/2)));
}

TEST_F(ScreenWrapperTest, WrapsLeftToTop)
{
    Vector location(-distanceMoved, bounds.y/2 + distanceMoved);
    Vector velocity(-distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2 - distanceMoved, distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsLeftToBottom)
{
    Vector location(-distanceMoved, bounds.y/2 - distanceMoved);
    Vector velocity(-distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2 - distanceMoved, bounds.y - distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsBottomToTop)
{
    Vector location(bounds.x/2, bounds.y + distanceMoved);
    Vector velocity(0, distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2, distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsBottomToLeft)
{
    Vector location(bounds.x/2 + distanceMoved, bounds.y + distanceMoved);
    Vector velocity(distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(distanceMoved, bounds.y/2 + distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsBottomToRight)
{
    Vector location(bounds.x/2 - distanceMoved, bounds.y + distanceMoved);
    Vector velocity(-distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x - distanceMoved, bounds.y/2 + distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsRightToLeft)
{
    Vector location(bounds.x + distanceMoved, bounds.y/2);
    Vector velocity(distanceMoved/timeElapsed, 0);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(distanceMoved, bounds.y/2)));
}

TEST_F(ScreenWrapperTest, WrapsRightToTop)
{
    Vector location(bounds.x + distanceMoved, bounds.y/2 + distanceMoved);
    Vector velocity(distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2 + distanceMoved, distanceMoved)));
}

TEST_F(ScreenWrapperTest, WrapsRightToBottom)
{
    Vector location(bounds.x + distanceMoved, bounds.y/2 - distanceMoved);
    Vector velocity(distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    screenWrapper.wrap(location, velocity, timeElapsed);
    EXPECT_THAT(location, Eq(Vector(bounds.x/2 + distanceMoved, bounds.y - distanceMoved)));
}
