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

//TEST_F(LocationGeneratorTest, GeneratesRandomLocation)
//{
//    _random.sequence.insert(0.375);
//    _random.sequence.insert(30);
//    EXPECT_THAT(_locationGenerator.generateLocation(20,50), Eq(Vector(,100)));
//}
