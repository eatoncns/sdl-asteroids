#include <gmock/gmock.h>
#include <Asteroid.hpp>
#include <MoveableObjectTest.hpp>

using namespace pjm;
using ::testing::ElementsAre;

class AsteroidTest : public MoveableObjectTest
{
    protected:
        AsteroidTest()
            : _asteroid(_imageLoader, _wrapper)
        {
            _asteroid.initialise(_initialLocation);
        }

        Asteroid _asteroid;
};

TEST_F(AsteroidTest, RendersImageAtCurrentLocation)
{
    _asteroid.render();
    EXPECT_THAT(_testRenderable.renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}
