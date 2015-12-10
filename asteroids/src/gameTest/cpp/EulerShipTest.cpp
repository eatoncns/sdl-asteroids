#include <gmock/gmock.h>
#include <EulerShip.hpp>
#include <ShipAction.hpp>
#include <Rectangle.hpp>
#include <MoveableObjectTest.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
#include <TestBulletLoader.hpp>
#include <boost/math/special_functions/round.hpp>
#include <math.h>

using namespace pjm;
using namespace boost::math;
using boost::shared_ptr;
using ::testing::Eq;
using ::testing::Le;
using ::testing::_;

class EulerShipTest : public MoveableObjectTest
{
    protected:
        EulerShipTest()
            : _timer(0),
              _bulletLoader(new TestBulletLoader(_timer)),
              _ship(_wrapper, _bulletLoader)
        {
            _ship.initialise(_initialLocation, _imageLoader);
        }

        unsigned int timeToRotate(double iAngle)
        {
            return iround(iAngle/EulerShip::ROTATION_FACTOR);
        }

        void expectShipToRenderAt(const Vector& iLocation, const double iAngle)
        {
            expectObjectToRenderAt(_ship, iLocation, iAngle);
        }

        void expectShipToRenderAtAngle(const double iAngle)
        {
            expectObjectToRenderAtAngle(_ship, iAngle);
        }

        void expectShipToRenderAtLocation(const Vector& iLocation)
        {
            expectObjectToRenderAtLocation(_ship, iLocation);
        }

        TestTimer _timer;
        shared_ptr<TestBulletLoader> _bulletLoader;
        EulerShip _ship;
};


TEST_F(EulerShipTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_ship.initialise(_initialLocation, _imageLoader));
}

TEST_F(EulerShipTest, IntialisesAtGivenLocationWithZeroAngle)
{
    expectShipToRenderAt(_initialLocation, 0.0);
}

TEST_F(EulerShipTest, RotatesLeft)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().turningLeft(), timeElapsed);
    expectShipToRenderAtAngle(-(timeElapsed*EulerShip::ROTATION_FACTOR));
}

TEST_F(EulerShipTest, RotatesRight)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().turningRight(), timeElapsed);
    expectShipToRenderAtAngle(timeElapsed*EulerShip::ROTATION_FACTOR);
}

TEST_F(EulerShipTest, DoesNotRotateWhenNoActionTaken)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction(), timeElapsed);
    expectShipToRenderAtAngle(0.0);
}

TEST_F(EulerShipTest, RotationAloneDoesNotCauseLocationChange)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().turningRight(), timeElapsed);
    expectShipToRenderAtLocation(_initialLocation);
}

TEST_F(EulerShipTest, DoesConstantEulerAcceleration)
{
    unsigned int firstTimeElapsed = 5;
    _ship.update(ShipAction().accelerating(), firstTimeElapsed);
    // l = v*t = a*t^2
    float yMovement = firstTimeElapsed*firstTimeElapsed*EulerShip::ACC_FACTOR;
    float yPos = _initialLocation.y - yMovement;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, yPos));

    unsigned int secondTimeElapsed = 6;
    _ship.update(ShipAction().accelerating(), secondTimeElapsed);
    // l = t*v
    yMovement = secondTimeElapsed*(firstTimeElapsed*EulerShip::ACC_FACTOR +
                                   secondTimeElapsed*EulerShip::ACC_FACTOR);
    yPos = yPos - yMovement;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, yPos));
}

TEST_F(EulerShipTest, AccelerationAloneDoesNotCauseRotation)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().accelerating(), timeElapsed);
    expectShipToRenderAtAngle(0.0);
}

/*
TEST_F(EulerShipTest, ResetsAccelerationWhenNoActionTaken)
{
    accelerateFrom(_initialLocation, -45.0, 5);
    doNothingFor(5);
    EXPECT_THAT(_ship.getAcceleration().x, Eq(0));
    EXPECT_THAT(_ship.getAcceleration().y, Eq(0));
}
*/

TEST_F(EulerShipTest, AcceleratesLeft)
{
    unsigned int rotationTime = timeToRotate(45.0);
    _ship.update(ShipAction().accelerating().turningLeft(), rotationTime);
    float xPos = _initialLocation.x -
                 0.5*rotationTime*rotationTime*EulerShip::ACC_FACTOR;
    float yPos = _initialLocation.y -
                 0.5*rotationTime*rotationTime*EulerShip::ACC_FACTOR;
    expectShipToRenderAt(Vector(xPos, yPos), -45.0);
}

TEST_F(EulerShipTest, AcceleratesRight)
{
    unsigned int rotationTime = timeToRotate(45.0);
    _ship.update(ShipAction().accelerating().turningRight(), rotationTime);
    float xPos = _initialLocation.x +
                 0.5*rotationTime*rotationTime*EulerShip::ACC_FACTOR;
    float yPos = _initialLocation.y -
                 0.5*rotationTime*rotationTime*EulerShip::ACC_FACTOR;
    expectShipToRenderAt(Vector(xPos, yPos), 45.0);
}

TEST_F(EulerShipTest, DoesNotExceedMaximumVelocity)
{
    unsigned int timeForDoubleMaxVelocity =
        2*(EulerShip::MAX_VELOCITY/EulerShip::ACC_FACTOR);
    _ship.update(ShipAction().accelerating(), timeForDoubleMaxVelocity);
    float maxVelocityYPos = _initialLocation.y -
                            timeForDoubleMaxVelocity*EulerShip::MAX_VELOCITY;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, maxVelocityYPos));
}

TEST_F(EulerShipTest, CallsScreenWrapperOnUpdate)
{
    unsigned int time = 3;
    EXPECT_CALL(*_wrapper, wrap(_initialLocation, Vector(0, 0), time))
        .Times(1);
    _ship.update(ShipAction(), time);
}

TEST_F(EulerShipTest, HasBoundingBoxBasedOnImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _ship.getBoundingBox();
    float ratioLength = testLength*ObjectRenderer::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}

TEST_F(EulerShipTest, InitialisesUnexpired)
{
    EXPECT_THAT(_ship.isExpired(), Eq(false));
}

TEST_F(EulerShipTest, ExpiresOnCollisionWithAsteroid)
{
    TestAsteroid asteroid;
    _ship.collideWith(&asteroid);
    EXPECT_THAT(_ship.isExpired(), Eq(true));
}

TEST_F(EulerShipTest, OnlyCallsBulletLoaderForShootAction)
{
    EXPECT_CALL(*_bulletLoader, loadBullet(_, _))
        .Times(0);
    _ship.update(ShipAction(), 3);
}

TEST_F(EulerShipTest, CallsBulletLoaderWithShipInfo)
{
    double angle = 45.0;
    unsigned int rotationTime = timeToRotate(angle);
    EXPECT_CALL(*_bulletLoader, loadBullet(_initialLocation, angle));
    _ship.update(ShipAction().turningRight().shooting(), rotationTime);
}
