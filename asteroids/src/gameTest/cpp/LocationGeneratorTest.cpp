#include <gmock/gmock.h>
#include <LocationGenerator.hpp>
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
        LocationGenerator _locationGenerator;
};

TEST_F(LocationGeneratorTest, GeneratesRandomLocationWithinBoundsFromCentre)
{
    EXPECT_CALL(_random, uniformInRange(0,1))
        .WillOnce(Return(0.25));
    EXPECT_CALL(_random, uniformInRange(20,50))
        .WillOnce(Return(30));
    EXPECT_THAT(_locationGenerator.generateLocation(20,50), Eq(Vector(130,100)));
}
