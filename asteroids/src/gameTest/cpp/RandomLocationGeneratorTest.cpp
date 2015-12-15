#include <gmock/gmock.h>
#include <RandomLocationGenerator.hpp>
#include <ScreenInfo.hpp>
#include <TestRandomGenerator.hpp>
#include <Vector.hpp>

using namespace pjm;
using ::testing::Eq;
using ::testing::Return;

class LocationGeneratorTest : public ::testing::Test
{
    protected:
        LocationGeneratorTest()
            : _screenInfo("Test", 200, 200),
              _locationGenerator(_screenInfo, _random)
        {}

        ScreenInfo _screenInfo;
        TestRandomGenerator _random;
        RandomLocationGenerator _locationGenerator;
};

TEST_F(LocationGeneratorTest, GeneratesRandomLocationWithinBoundsFromCentre)
{
    float angleRatio = 0.25; // 0.25*360 = 90 degrees
    float distance = 30;
    Vector centre(_screenInfo.width/2, _screenInfo.height/2);
    EXPECT_CALL(_random, uniformInRange(0,1))
        .WillOnce(Return(angleRatio));
    EXPECT_CALL(_random, uniformInRange(20,50))
        .WillOnce(Return(distance));
    EXPECT_THAT(_locationGenerator.generateLocation(20,50),
                Eq(centre + Vector(distance, 0)));
}
