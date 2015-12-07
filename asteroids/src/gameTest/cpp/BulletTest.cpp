#include <gmock/gmock.h>
#include <Bullet.hpp>
#include <MoveableObjectTest.hpp>
#include <TestAsteroid.hpp>
#include <Rectangle.hpp>
#include <boost/math/special_functions/round.hpp>

using namespace pjm;
using boost::math::iround;
using ::testing::Eq;
using ::testing::ElementsAre;

class BulletTest : public MoveableObjectTest
{
    protected:
        BulletTest()
            : _bounds(110, 110),
              _angle(90.0),
              _bullet(_bounds)

        {
            _bullet.initialise(_initialLocation, _angle, _imageLoader);
        }

        void expectBulletToRenderAt(const Vector& iLocation, const double iAngle)
        {
            expectObjectToRenderAt(_bullet, iLocation, iAngle);
        }

        void expectBulletToRenderAtAngle(const double iAngle)
        {
            expectObjectToRenderAtAngle(_bullet, iAngle);
        }

        void expectBulletToRenderAtLocation(const Vector& iLocation)
        {
            expectObjectToRenderAtLocation(_bullet, iLocation);
        }

        Vector _bounds;
        double _angle;
        Bullet _bullet;
};


TEST_F(BulletTest, InitialiseReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_THAT(_bullet.initialise(_initialLocation, _angle, _imageLoader), Eq(false));
}

TEST_F(BulletTest, InitialiseReturnsTrueWhenImageLoadSucceeds)
{
    EXPECT_THAT(_bullet.initialise(_initialLocation, _angle, _imageLoader), Eq(true));
}

TEST_F(BulletTest, MovesWithFixedVelocityAlongGivenAngle)
{
    unsigned int timeElapsed = 5;
    _bullet.update(timeElapsed);
    expectBulletToRenderAtLocation(Vector(_initialLocation.x + Bullet::VELOCITY*5,
                                          _initialLocation.y));
}

TEST_F(BulletTest, DoesNotRotate)
{
    unsigned int timeElapsed = 5;
    _bullet.update(timeElapsed);
    expectBulletToRenderAtAngle(0.0);
}

TEST_F(BulletTest, InitialisesWithCorrectYAxisDirection)
{
    _angle = 180.0;
    _bullet.initialise(_initialLocation, _angle, _imageLoader);
    unsigned int timeElapsed = 5;
    _bullet.update(timeElapsed);
    expectBulletToRenderAtLocation(Vector(_initialLocation.x,
                                          _initialLocation.y + Bullet::VELOCITY*5));
}

TEST_F(BulletTest, IsNotExpiredWhileStillOnScreen)
{
    _bullet.update(5);
    EXPECT_THAT(_bullet.isExpired(), Eq(false));
}

TEST_F(BulletTest, ExpiresWhenMovesOffScreen)
{
    _bullet.update(100);
    EXPECT_THAT(_bullet.isExpired(), Eq(true));
}

TEST_F(BulletTest, RendersImageAtCurrentLocation)
{
    expectBulletToRenderAt(_initialLocation, 0.0);
}

TEST_F(BulletTest, HasBoundingBoxBasedOnScaledImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _bullet.getBoundingBox();
    float ratioLength = testLength*CollidableObject::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}

TEST_F(BulletTest, ExpiresOnCollisionWithAsteroid)
{
    TestAsteroid asteroid;
    _bullet.collideWith(&asteroid);
    EXPECT_THAT(_bullet.isExpired(), Eq(true));
}
