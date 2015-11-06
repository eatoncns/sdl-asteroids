#include <gmock/gmock.h>
#include <Ship.hpp>
#include <KeyPress.hpp>
#include <Rectangle.hpp>
#include <MoveableObjectTest.hpp>
#include <TestAsteroid.hpp>
#include <boost/math/special_functions/round.hpp>
#include <math.h>

using namespace pjm;
using namespace boost::math;
using boost::shared_ptr;
using ::testing::Eq;
using ::testing::Le;
using ::testing::ElementsAre;

struct ShipSpy : public Ship
{
    ShipSpy(shared_ptr<ScreenWrapper> iScreenWrapper)
        : Ship(iScreenWrapper)
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


class ShipTest : public MoveableObjectTest
{
    protected:
        ShipTest()
            : _ship(_wrapper)
        {
            _ship.initialise(_initialLocation, _imageLoader);
        }

        void update(ShipAction iAction, unsigned int iTime)
        {
            _ship.update(iAction, iTime);
        }

        void accelerateFor(unsigned int iTime)
        {
            ShipAction action; action.accelerate = true;
            update(action, iTime);
        }

        void turnLeftFor(unsigned int iTime)
        {
            ShipAction action; action.turn_left = true;
            update(action, iTime);
        }

        void turnRightFor(unsigned int iTime)
        {
            ShipAction action; action.turn_right = true;
            update(action, iTime);
        }

        void accelerateLeftFor(unsigned int iTime)
        {
            ShipAction action;
            action.accelerate = true;
            action.turn_left = true;
            update(action, iTime);
        }

        void accelerateRightFor(unsigned int iTime)
        {
            ShipAction action;
            action.accelerate = true;
            action.turn_right = true;
            update(action, iTime);
        }

        void doNothingFor(unsigned int iTime)
        {
            update(ShipAction(), iTime);
        }

        unsigned int timeToRotate(double iAngle)
        {
            return iround(iAngle/Ship::ROTATION_FACTOR);
        }

        void turnTo(double iAngle)
        {
            unsigned int time = timeToRotate(fabs(iAngle));
            iAngle > 0 ? turnRightFor(time) : turnLeftFor(time);
        }

        void accelerateFrom(const Vector& iLocation, double iAngle, unsigned int iTime)
        {
            _ship.initialise(iLocation, _imageLoader);
            turnTo(iAngle);
            accelerateFor(iTime);
        }

        ShipSpy _ship;
};


TEST_F(ShipTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_ship.initialise(_initialLocation, _imageLoader));
}

TEST_F(ShipTest, RendersImageAtCurrentLocation)
{
    _ship.render();
    EXPECT_THAT(_testRenderable->renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
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

TEST_F(ShipTest, CallsScreenWrapperOnUpdate)
{
    EXPECT_CALL(*_wrapper, wrap(_initialLocation, Vector(0, 0), 3))
        .Times(1);
    doNothingFor(3);
}

TEST_F(ShipTest, HasBoundingBoxBasedOnImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _ship.getBoundingBox();
    float ratioLength = testLength*CollidableObject::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}

TEST_F(ShipTest, InitialisesUnexpired)
{
    EXPECT_THAT(_ship.isExpired(), Eq(false));
}

TEST_F(ShipTest, ExpiresOnCollisionWithAsteroid)
{
    TestAsteroid asteroid;
    _ship.collideWith(&asteroid);
    EXPECT_THAT(_ship.isExpired(), Eq(true));
}
