#include <gmock/gmock.h>
#include <LocationGenerator.hpp>
#include <TestRandomGenerator.hpp>
#include <Vector.hpp>

using namespace pjm;
using ::testing::Eq;

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

TEST_F(LocationGeneratorTest, GeneratesRandomLocation)
{
    EXPECT_THAT(_locationGenerator.generateLocation(1,1), Eq(Vector(100,100)));
}
