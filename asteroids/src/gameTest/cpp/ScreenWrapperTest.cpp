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
              location(0, 0),
              velocity(0, 0),
              timeElapsed(1),
              distanceMoved(0.5),
              screenWrapper(bounds)
        {}

        void testLocationEq(float iX, float iY)
        {
            screenWrapper.wrap(location, velocity, timeElapsed);
            EXPECT_THAT(location, Eq(Vector(iX, iY)));
        }

        Vector bounds;
        Vector location;
        Vector velocity;
        unsigned int timeElapsed;
        float distanceMoved;
        ScreenWrapper screenWrapper;
};

TEST_F(ScreenWrapperTest, WrapsTopToBottom)
{
    location = Vector(bounds.x/2, -distanceMoved);
    velocity = Vector(0, -distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2, bounds.y - distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsTopToLeft)
{
    location = Vector(bounds.x/2 + distanceMoved, -distanceMoved);
    velocity = Vector(distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    testLocationEq(distanceMoved, bounds.y/2 - distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsTopToRight)
{
    location = Vector(bounds.x/2 - distanceMoved, -distanceMoved);
    velocity = Vector(-distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    testLocationEq(bounds.x - distanceMoved, bounds.y/2 - distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsLeftToRight)
{
    location = Vector(-distanceMoved, bounds.y/2);
    velocity = Vector(-distanceMoved/timeElapsed, 0);
    testLocationEq(bounds.x - distanceMoved, bounds.y/2);
}

TEST_F(ScreenWrapperTest, WrapsLeftToTop)
{
    location = Vector(-distanceMoved, bounds.y/2 + distanceMoved);
    velocity = Vector(-distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2 - distanceMoved, distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsLeftToBottom)
{
    location = Vector(-distanceMoved, bounds.y/2 - distanceMoved);
    velocity = Vector(-distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2 - distanceMoved, bounds.y - distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsBottomToTop)
{
    location = Vector(bounds.x/2, bounds.y + distanceMoved);
    velocity = Vector(0, distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2, distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsBottomToLeft)
{
    location = Vector(bounds.x/2 + distanceMoved, bounds.y + distanceMoved);
    velocity = Vector(distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    testLocationEq(distanceMoved, bounds.y/2 + distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsBottomToRight)
{
    location = Vector(bounds.x/2 - distanceMoved, bounds.y + distanceMoved);
    velocity = Vector(-distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    testLocationEq(bounds.x - distanceMoved, bounds.y/2 + distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsRightToLeft)
{
    location = Vector(bounds.x + distanceMoved, bounds.y/2);
    velocity = Vector(distanceMoved/timeElapsed, 0);
    testLocationEq(distanceMoved, bounds.y/2);
}

TEST_F(ScreenWrapperTest, WrapsRightToTop)
{
    location = Vector(bounds.x + distanceMoved, bounds.y/2 + distanceMoved);
    velocity = Vector(distanceMoved/timeElapsed, distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2 + distanceMoved, distanceMoved);
}

TEST_F(ScreenWrapperTest, WrapsRightToBottom)
{
    location = Vector(bounds.x + distanceMoved, bounds.y/2 - distanceMoved);
    velocity = Vector(distanceMoved/timeElapsed, -distanceMoved/timeElapsed);
    testLocationEq(bounds.x/2 + distanceMoved, bounds.y - distanceMoved);
}
