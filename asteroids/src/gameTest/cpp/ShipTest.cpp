#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Vector.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using ::testing::ElementsAre;

class ShipTest : public ::testing::Test
{
    protected:
        ShipTest()
            : _initialLocation(100, 100),
              _ship(_initialLocation, _shipImage)
        {}

        void accelerateFor(int iTime)
        {
            _ship.update(Ship::ACCELERATE, iTime);
            _ship.render(); 
        }

        Vector _initialLocation;
        TestRenderable _shipImage;
        Ship _ship;
};


TEST_F(ShipTest, RendersImageAtCurrentLocation)
{
    _ship.render();
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(_initialLocation));
}

TEST_F(ShipTest, DoesVerletAcceleration)
{
    accelerateFor(5);
    accelerateFor(6);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    float secondYPos = 2*firstYPos - _initialLocation.y - 36*2*Ship::ACC_FACTOR;
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(
                  Vector(_initialLocation.x, firstYPos),
                  Vector(_initialLocation.x, secondYPos))); 
}
