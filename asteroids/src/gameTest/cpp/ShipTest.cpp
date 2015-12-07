#include <gmock/gmock.h>
#include <Ship.hpp>
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

class ShipTest : public MoveableObjectTest
{
    protected:
        ShipTest()
            : _timer(0),
              _bulletLoader(new TestBulletLoader(_timer)),
              _ship(_wrapper, _bulletLoader)
        {
            _ship.initialise(_initialLocation, _imageLoader);
        }

        unsigned int timeToRotate(double iAngle)
        {
            return iround(iAngle/Ship::ROTATION_FACTOR);
        }

        void expectShipToRenderAt(const Vector& iLocation, const double iAngle)
        {
            _ship.render();
            ASSERT_FALSE(_testRenderable->renderCalls.empty());
            EXPECT_THAT(_testRenderable->renderCalls.back(),
                        Eq(std::make_pair(iLocation, iAngle)));
        }

        void expectShipToRenderAtAngle(const double iAngle)
        {
            expectShipToRenderAt(_initialLocation, iAngle);
        }

        void expectShipToRenderAtLocation(const Vector& iLocation)
        {
            expectShipToRenderAt(iLocation, 0.0);
        }

        TestTimer _timer;
        shared_ptr<TestBulletLoader> _bulletLoader;
        Ship _ship;
};


TEST_F(ShipTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_ship.initialise(_initialLocation, _imageLoader));
}

TEST_F(ShipTest, IntialisesAtGivenLocationWithZeroAngle)
{
    expectShipToRenderAt(_initialLocation, 0.0);
}

TEST_F(ShipTest, RotatesLeft)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().turningLeft(), timeElapsed);
    expectShipToRenderAtAngle(-(timeElapsed*Ship::ROTATION_FACTOR));
}

TEST_F(ShipTest, RotatesRight)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction().turningRight(), timeElapsed);
    expectShipToRenderAtAngle(timeElapsed*Ship::ROTATION_FACTOR);
}

TEST_F(ShipTest, DoesNotRotateWhenNoActionTaken)
{
    unsigned int timeElapsed = 5;
    _ship.update(ShipAction(), timeElapsed);
    expectShipToRenderAtAngle(0.0);
}

TEST_F(ShipTest, DoesConstantEulerAcceleration)
{
    unsigned int firstTimeElapsed = 5;
    _ship.update(ShipAction().accelerating(), firstTimeElapsed);
    // l = v*t = a*t^2
    float yMovement = firstTimeElapsed*firstTimeElapsed*Ship::ACC_FACTOR;
    float yPos = _initialLocation.y - yMovement;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, yPos));

    unsigned int secondTimeElapsed = 6;
    _ship.update(ShipAction().accelerating(), secondTimeElapsed);
    // l = t*v
    yMovement = secondTimeElapsed*(firstTimeElapsed*Ship::ACC_FACTOR + secondTimeElapsed*Ship::ACC_FACTOR);
    yPos = yPos - yMovement;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, yPos));
}

/*
TEST_F(ShipTest, ResetsAccelerationWhenNoActionTaken)
{
    accelerateFrom(_initialLocation, -45.0, 5);
    doNothingFor(5);
    EXPECT_THAT(_ship.getAcceleration().x, Eq(0));
    EXPECT_THAT(_ship.getAcceleration().y, Eq(0));
}
*/

TEST_F(ShipTest, AcceleratesLeft)
{
    unsigned int rotationTime = timeToRotate(45.0);
    _ship.update(ShipAction().accelerating().turningLeft(), rotationTime);
    float xPos = _initialLocation.x - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    float yPos = _initialLocation.y - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    expectShipToRenderAt(Vector(xPos, yPos), -45.0);
}

TEST_F(ShipTest, AcceleratesRight)
{
    unsigned int rotationTime = timeToRotate(45.0);
    _ship.update(ShipAction().accelerating().turningRight(), rotationTime);
    float xPos = _initialLocation.x + 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    float yPos = _initialLocation.y - 0.5*rotationTime*rotationTime*Ship::ACC_FACTOR;
    expectShipToRenderAt(Vector(xPos, yPos), 45.0);
}

TEST_F(ShipTest, DoesNotExceedMaximumVelocity)
{
    unsigned int timeForDoubleMaxVelocity = 2*(Ship::MAX_VELOCITY/Ship::ACC_FACTOR);
    _ship.update(ShipAction().accelerating(), timeForDoubleMaxVelocity);
    float maxVelocityYPos = _initialLocation.y - timeForDoubleMaxVelocity*Ship::MAX_VELOCITY;
    expectShipToRenderAtLocation(Vector(_initialLocation.x, maxVelocityYPos));
}

TEST_F(ShipTest, CallsScreenWrapperOnUpdate)
{
    unsigned int time = 3;
    EXPECT_CALL(*_wrapper, wrap(_initialLocation, Vector(0, 0), time))
        .Times(1);
    _ship.update(ShipAction(), time);
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

TEST_F(ShipTest, OnlyCallsBulletLoaderForShootAction)
{
    EXPECT_CALL(*_bulletLoader, loadBullet(_, _))
        .Times(0);
    _ship.update(ShipAction(), 3);
}

TEST_F(ShipTest, CallsBulletLoaderWithShipInfo)
{
    double angle = 45.0;
    unsigned int rotationTime = timeToRotate(angle);
    EXPECT_CALL(*_bulletLoader, loadBullet(_initialLocation, angle));
    _ship.update(ShipAction().turningRight().shooting(), rotationTime);
}
