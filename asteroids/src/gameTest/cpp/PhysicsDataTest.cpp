#include <gmock/gmock.h>
#include <PhysicsData.hpp>

using namespace pjm;
using ::testing::Eq;

class PhysicsDataTest : public ::testing::Test
{
    protected:
        PhysicsData data;
};

TEST_F(PhysicsDataTest, DefaultsLocationToOrigin)
{
    EXPECT_THAT(data.location, Eq(Vector(0,0)));
}

TEST_F(PhysicsDataTest, DefaultsVelocityToZero)
{
    EXPECT_THAT(data.velocity, Eq(Vector(0,0)));
}

TEST_F(PhysicsDataTest, UpdatesLocationBasedOnVelocity)
{
    data.velocity = Vector(2,5);
    unsigned int timeElapsed = 3;
    data.updateLocation(timeElapsed);
    EXPECT_THAT(data.location, Eq(Vector(6,15)));
}
