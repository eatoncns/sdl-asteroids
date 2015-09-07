#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Vector.hpp>
#include <TestRenderable.hpp>
#include <TestImageLoader.hpp>

using namespace pjm;
using ::testing::Eq;
using ::testing::ElementsAre;

struct ShipSpy : public Ship
{
    ShipSpy(ImageLoader& iImageLoader)
        : Ship(iImageLoader)
    {}

    Vector getLocation() const
    {
        return _location;
    }

    Vector getVelocity() const
    {
        return _velocity;
    }

    Vector getAcceleration() const
    {
        return _acceleration;
    }

    double getAngle() const
    {
        return _angle;
    }
};

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
        }

        void accelerateFor(unsigned int iTime)
        {
            update(Ship::ACCELERATE, iTime);
        }

        void turnLeftFor(unsigned int iTime)
        {
            update(Ship::TURN_LEFT, iTime);
        }
        
        void turnRightFor(unsigned int iTime)
        {
            update(Ship::TURN_RIGHT, iTime);
        }

        void accelerateLeftFor(unsigned int iTime)
        {
            update(Ship::ACCELERATE_LEFT, iTime);
        }
        
        void accelerateRightFor(unsigned int iTime)
        {
            update(Ship::ACCELERATE_RIGHT, iTime);
        }

        void doNothingFor(unsigned int iTime)
        {
            update(Ship::NONE, iTime);
        }

        Vector _initialLocation;
        Vector _bounds;
        TestImageLoader _imageLoader;
        TestRenderable _shipImage;
        ShipSpy _ship;
};


TEST_F(ShipTest, RendersImageAtCurrentLocation)
{
    _ship.render();
    EXPECT_THAT(_shipImage.renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}

TEST_F(ShipTest, DoesEulerAcceleration)
{
    accelerateFor(5);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, firstYPos)));
    accelerateFor(6);
    float secondYPos = firstYPos - 6*(5*Ship::ACC_FACTOR + 6*2*Ship::ACC_FACTOR);
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, secondYPos))); 
}

TEST_F(ShipTest, ReducesAccelerationWhenNoActionTaken)
{
    accelerateFor(5);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, firstYPos)));
    doNothingFor(5);
    float secondYPos = firstYPos + (firstYPos - _initialLocation.y);
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, secondYPos)));
}

TEST_F(ShipTest, DoesNotReduceAccelerationBelowZeroWhenNoActionTaken)
{
    doNothingFor(5);
    EXPECT_THAT(_ship.getLocation(), Eq(_initialLocation));
}

TEST_F(ShipTest, WrapsToBottomOfScreenWhenExitingTop)
{
    _ship.initialise(Vector(0,0), _bounds);
    accelerateFor(100);
    float wrappedYPos = _bounds.y - 10000*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(0, wrappedYPos)));
}

TEST_F(ShipTest, DoesNotExceedMaximumVelocity)
{
    accelerateFor(10000000);
    EXPECT_THAT(_ship.getVelocity().y, Eq(Ship::MAX_VELOCITY));
}

TEST_F(ShipTest, ResetsAccelerationAtMaximumVelocity)
{
    accelerateFor(10000000);
    doNothingFor(1);
    EXPECT_THAT(_ship.getAcceleration().y, Eq(0));
}

TEST_F(ShipTest, RotatesLeft)
{
    turnLeftFor(5);
    EXPECT_THAT(_ship.getAngle(), Eq(-5*Ship::ROTATION_FACTOR));
}

TEST_F(ShipTest, RotatesRight)
{
    turnRightFor(5);
    EXPECT_THAT(_ship.getAngle(), Eq(5*Ship::ROTATION_FACTOR));
}

TEST_F(ShipTest, DoesNotRotateWhenNoActionTaken)
{
    doNothingFor(5);
    EXPECT_THAT(_ship.getAngle(), Eq(0.0));
}

TEST_F(ShipTest, AcceleratesLeft)
{
    accelerateLeftFor(10);
    float yPos = _initialLocation.y - 100*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, yPos)));
    EXPECT_THAT(_ship.getAngle(), Eq(-10*Ship::ROTATION_FACTOR));
}

TEST_F(ShipTest, AcceleratesRight)
{
    accelerateRightFor(10);
    float yPos = _initialLocation.y - 100*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, yPos)));
    EXPECT_THAT(_ship.getAngle(), Eq(10*Ship::ROTATION_FACTOR));
}
