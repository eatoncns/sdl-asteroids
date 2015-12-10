#include <gmock/gmock.h>
#include <FixedSpeedAsteroid.hpp>
#include <Rectangle.hpp>
#include <MoveableObjectTest.hpp>
#include <TestAsteroid.hpp>
#include <TestBullet.hpp>
#include <TestRandomGenerator.hpp>
#include <boost/math/special_functions/round.hpp>

using namespace pjm;
using boost::shared_ptr;
using boost::math::iround;
using ::testing::Eq;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Return;

class FixedSpeedAsteroidTest : public MoveableObjectTest
{
    protected:
        FixedSpeedAsteroidTest()
            : _asteroid(_wrapper),
              // velocity component to give 45 degree angle
              // i.e. same amount in each axis
              _velocityComponent(sin(45*M_PI/180.0)*FixedSpeedAsteroid::VELOCITY)
        {
            ON_CALL(_random, uniformInRange(_,_))
                .WillByDefault(Return(0.375));
            _asteroid.initialise(_initialLocation, _imageLoader, _random);
        }

        void expectAsteroidToRenderAt(const Vector& iLocation, const double iAngle)
        {
            expectObjectToRenderAt(_asteroid, iLocation, iAngle);
        }

        void expectAsteroidToRenderAtAngle(const double iAngle)
        {
            expectObjectToRenderAtAngle(_asteroid, iAngle);
        }

        void expectAsteroidToRenderAtLocation(const Vector& iLocation)
        {
            expectObjectToRenderAtLocation(_asteroid, iLocation);
        }

        NiceMock<TestRandomGenerator> _random;
        FixedSpeedAsteroid _asteroid;
        float _velocityComponent;
};


TEST_F(FixedSpeedAsteroidTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_asteroid.initialise(_initialLocation, _imageLoader, _random));
}

TEST_F(FixedSpeedAsteroidTest, IntialisesAtGivenLocationWithZeroAngle)
{
    expectAsteroidToRenderAt(_initialLocation, 0.0);
}

TEST_F(FixedSpeedAsteroidTest, MovesWithConstantVelocity)
{
    unsigned int timeElapsed = 5;
    _asteroid.update(timeElapsed);
    Vector offset(_velocityComponent*timeElapsed,
                  _velocityComponent*timeElapsed);
    expectAsteroidToRenderAtLocation(_initialLocation + offset);
}

TEST_F(FixedSpeedAsteroidTest, DoesNotRotate)
{
    unsigned int timeElapsed = 5;
    _asteroid.update(timeElapsed);
    expectAsteroidToRenderAtAngle(0.0);
}

TEST_F(FixedSpeedAsteroidTest, CallsScreenWrapperOnUpdate)
{
    float distanceComponent = _velocityComponent*5;
    Vector location(_initialLocation.x + distanceComponent, _initialLocation.y + distanceComponent);
    Vector velocity(_velocityComponent, _velocityComponent);
    EXPECT_CALL(*_wrapper, wrap(location, velocity, 5));
    _asteroid.update(5);
}

TEST_F(FixedSpeedAsteroidTest, HasBoundingBoxBasedOnScaledImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _asteroid.getBoundingBox();
    float ratioLength = testLength*ObjectRenderer::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}

TEST_F(FixedSpeedAsteroidTest, SwapsDirectionWithOtherAsteroidOnCollision)
{
    TestAsteroid otherAsteroid;
    otherAsteroid.normalisedDirection = Vector(1, 0);
    _asteroid.collideWith(&otherAsteroid);
    float asteroidNorm = sqrt(2.0)/2; // as _asteroid is at 45 degrees
    ASSERT_THAT(otherAsteroid.setNormalisedDirectionCalls.empty(), Eq(false));
    EXPECT_THAT(otherAsteroid.setNormalisedDirectionCalls,
                ElementsAre(Vector(asteroidNorm,asteroidNorm)));
    unsigned int timeElapsed = 1;
    _asteroid.update(timeElapsed);
    expectAsteroidToRenderAtLocation(_initialLocation +
                                     Vector(FixedSpeedAsteroid::VELOCITY,0));
}

TEST_F(FixedSpeedAsteroidTest, IsNotExpiredOnInit)
{
    EXPECT_THAT(_asteroid.isExpired(), Eq(false));
}

TEST_F(FixedSpeedAsteroidTest, ExpiresOnCollisionWithBullet)
{
    TestBullet bullet;
    _asteroid.collideWith(&bullet);
    EXPECT_THAT(_asteroid.isExpired(), Eq(true));
}
