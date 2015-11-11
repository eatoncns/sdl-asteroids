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
using ::testing::ElementsAre;
using ::testing::_;

struct ShipSpy : public Ship
{
    ShipSpy(shared_ptr<ScreenWrapper> iScreenWrapper,
            shared_ptr<BulletLoader> iBulletLoader)
        : Ship(iScreenWrapper, iBulletLoader)
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
            : _timer(0),
              _bulletLoader(new TestBulletLoader(_timer)),
              _ship(_wrapper, _bulletLoader)
        {
            _ship.initialise(_initialLocation, _imageLoader);
        }

        void update(ShipAction iAction, unsigned int iTime)
        {
            _ship.update(iAction, iTime);
        }

        void accelerateFor(unsigned int iTime)
        {
            update(ShipAction().accelerating(), iTime);
        }

        void turnLeftFor(unsigned int iTime)
        {
            update(ShipAction().turningLeft(), iTime);
        }

        void turnRightFor(unsigned int iTime)
        {
            update(ShipAction().turningRight(), iTime);
        }

        void accelerateLeftFor(unsigned int iTime)
        {
            update(ShipAction().accelerating().turningLeft(), iTime);
        }

        void accelerateRightFor(unsigned int iTime)
        {
            update(ShipAction().accelerating().turningRight(), iTime);
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

        void shoot()
        {
            update(ShipAction().shooting(), 3);
        }

        TestTimer _timer;
        shared_ptr<TestBulletLoader> _bulletLoader;
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

TEST_F(ShipTest, OnlyCallsBulletLoaderForShootAction)
{
    EXPECT_CALL(*_bulletLoader, loadBullet(_, _))
        .Times(0);
    doNothingFor(5);
}

TEST_F(ShipTest, CallsBulletLoaderWithShipInfo)
{
    EXPECT_CALL(*_bulletLoader, loadBullet(_initialLocation, Vector(0, 0)));
    shoot();
}
