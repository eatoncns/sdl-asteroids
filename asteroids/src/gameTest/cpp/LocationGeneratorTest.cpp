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
            : _locationGenerator(_random)
        {}

        TestRandomGenerator _random;
        LocationGenerator _locationGenerator;
};

TEST_F(LocationGeneratorTest, GeneratesFixedLocation)
{
    EXPECT_THAT(_locationGenerator.generateLocation(1,1), Eq(Vector(100,100)));
}
