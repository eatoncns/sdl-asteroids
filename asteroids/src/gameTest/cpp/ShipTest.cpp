#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Vector.hpp>
#include <TestRenderable.hpp>
#include <TestImageLoader.hpp>

using namespace pjm;
using ::testing::ElementsAre;

class ShipTest : public ::testing::Test
{
    protected:
        ShipTest()
            : _initialLocation(100, 100),
              _bounds(200, 200),
              _ship(_imageLoader)
        {
            _imageLoader.renderable = &_shipImage;
            _ship.initialise(_initialLocation, _bounds);
        }

        void update(Ship::Action iAction, unsigned int iTime)
        {
            _ship.update(iAction, iTime);
            _ship.render(); 
        }

        void accelerateFor(unsigned int iTime)
        {
            update(Ship::ACCELERATE, iTime);
        }

        void doNothingFor(unsigned int iTime)
        {
            update(Ship::NONE, iTime);
        }

        Vector _initialLocation;
        Vector _bounds;
        TestImageLoader _imageLoader;
        TestRenderable _shipImage;
        Ship _ship;
};


TEST_F(ShipTest, RendersImageAtCurrentLocation)
{
    _ship.render();
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(_initialLocation));
}

TEST_F(ShipTest, DoesEulerAcceleration)
{
    accelerateFor(5);
    accelerateFor(6);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    float secondYPos = firstYPos - 6*(5*Ship::ACC_FACTOR + 6*2*Ship::ACC_FACTOR);
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(
                  Vector(_initialLocation.x, firstYPos),
                  Vector(_initialLocation.x, secondYPos))); 
}

TEST_F(ShipTest, ReducesAccelerationWhenNoActionTaken)
{
    accelerateFor(5);
    doNothingFor(5);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    float secondYPos = firstYPos + (firstYPos - _initialLocation.y);
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(
                  Vector(_initialLocation.x, firstYPos),
                  Vector(_initialLocation.x, secondYPos)));
}

TEST_F(ShipTest, DoesNotReduceAccelerationBelowZeroWhenNoActionTaken)
{
    doNothingFor(5);
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(_initialLocation)); 
}

//TEST_F(ShipTest, WrapsToBottomOfScreenWhenExitingTop)
//{
//    _ship.initialise(Vector(0,0), _bounds);
//    accelerateFor(20);
//    float wrappedYPos = _bounds.y - 10000*Ship::ACC_FACTOR;
//    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(Vector(0, wrappedYPos)));
//}
