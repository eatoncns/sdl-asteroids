#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Vector.hpp>
#include <TestRenderable.hpp>
#include <TestImageLoader.hpp>
#include <boost/math/special_functions/round.hpp>
#include <math.h>

using namespace pjm;
using namespace boost::math;
using ::testing::Eq;
using ::testing::Le;
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

        unsigned int timeToRotate(double iAngle)
        {
            return iround(iAngle/Ship::ROTATION_FACTOR);
        }

        void turnTo(double iAngle)
        {
            unsigned int time = timeToRotate(abs(iAngle));
            iAngle > 0 ? turnRightFor(time) : turnLeftFor(time);
        }

        void accelerateFrom(const Vector& iLocation, double iAngle, unsigned int iTime)
        {
            _ship.initialise(iLocation, _bounds);
            turnTo(iAngle);
            accelerateFor(iTime);
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

TEST_F(ShipTest, DoesConstantEulerAcceleration)
{
    accelerateFor(5);
    float firstYPos = _initialLocation.y - 25*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, firstYPos)));
    accelerateFor(6);
    float secondYPos = firstYPos - 6*(5*Ship::ACC_FACTOR + 6*Ship::ACC_FACTOR);
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_initialLocation.x, secondYPos))); 
}

TEST_F(ShipTest, ResetsAccelerationWhenNoActionTaken)
{
    accelerateFrom(_initialLocation, -45.0, 5);
    doNothingFor(5);
    EXPECT_THAT(_ship.getAcceleration().x, Eq(0));
    EXPECT_THAT(_ship.getAcceleration().y, Eq(0));
}

TEST_F(ShipTest, AcceleratesLeft)
{
    unsigned int rotationTime = timeToRotate(45.0);
    accelerateLeftFor(rotationTime);
    float xPos = _initialLocation.x - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    float yPos = _initialLocation.y - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(xPos, yPos)));
    EXPECT_THAT(_ship.getAngle(), Eq(-45.0));
}

TEST_F(ShipTest, AcceleratesRight)
{
    unsigned int rotationTime = timeToRotate(45.0);
    accelerateRightFor(rotationTime);
    float xPos = _initialLocation.x + 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    float yPos = _initialLocation.y - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(xPos, yPos)));
    EXPECT_THAT(_ship.getAngle(), Eq(45.0));
}

TEST_F(ShipTest, DoesNotExceedMaximumVelocity)
{
    turnTo(45.0);
    accelerateFor(10000000);
    EXPECT_THAT(_ship.getVelocity().squareSum(), Le(Ship::MAX_VELOCITY));
}

TEST_F(ShipTest, WrapsToLineOfVelocityTopToBottom)
{
    accelerateFrom(Vector(_bounds.x/2, 0), 0.0, 100);
    float wrappedYPos = _bounds.y - 10000*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(_bounds.x/2, wrappedYPos)));
}

TEST_F(ShipTest, WrapsToLineOfVelocityTopToLeft)
{
    accelerateFrom(Vector(_bounds.x/2, 0), 45.0, 100);
    float distanceMoved = 100*100*0.5*Ship::ACC_FACTOR;
    float wrappedXPos = distanceMoved;
    float wrappedYPos = (_bounds.x/2) - distanceMoved;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(wrappedXPos, wrappedYPos)));
}

TEST_F(ShipTest, WrapsToLineOfVelocityTopToRight)
{
    accelerateFrom(Vector(_bounds.x/2, 0), -45.0, 100);
    float distanceMoved = 100*100*0.5*Ship::ACC_FACTOR;
    float wrappedXPos = _bounds.x - distanceMoved;
    float wrappedYPos = (_bounds.x/2) - distanceMoved;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(wrappedXPos, wrappedYPos)));
}

TEST_F(ShipTest, WrapsToLineOfVelocityLeftToRight)
{
    accelerateFrom(Vector(0,1), -90.0, 100);
    float wrappedXPos = _bounds.x - 10000*Ship::ACC_FACTOR;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(wrappedXPos, 1)));
}

TEST_F(ShipTest, WrapsLineOfVelocityLeftToTop)
{
    accelerateFrom(Vector(0, _bounds.y/2), -135.0, 100);
    float distanceMoved = 100*100*0.5*Ship::ACC_FACTOR;
    float wrappedXPos = (_bounds.x/2) - distanceMoved;
    float wrappedYPos = distanceMoved;
    EXPECT_THAT(_ship.getLocation(), Eq(Vector(wrappedXPos, wrappedYPos)));
}
