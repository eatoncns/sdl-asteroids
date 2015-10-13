#include <gmock/gmock.h>
#include <Bullet.hpp>
#include <MoveableObjectTest.hpp>
#include <Rectangle.hpp>
#include <boost/math/special_functions/round.hpp>

using namespace pjm;
using boost::math::iround;
using ::testing::Eq;
using ::testing::ElementsAre;

struct BulletSpy : public Bullet
{
    BulletSpy(const Vector& iBounds)
        : Bullet(iBounds)
    {}

    Vector& getVelocity()
    {
        return _velocity;
    }

    Vector& getLocation()
    {
        return _location;
    }
};

class BulletTest : public MoveableObjectTest
{
    protected:
        BulletTest()
            : _bounds(200, 200),
              _shooterVelocity(0.5, 0),
              _bullet(_bounds)

        {
            _bullet.initialise(_initialLocation, _shooterVelocity, _imageLoader);
        }

        Vector _bounds;
        Vector _shooterVelocity;
        BulletSpy _bullet;
};


TEST_F(BulletTest, InitialiseReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_THAT(_bullet.initialise(_initialLocation, _shooterVelocity, _imageLoader), Eq(false));
}

TEST_F(BulletTest, InitialiseReturnsTrueWhenImageLoadSucceeds)
{
    EXPECT_THAT(_bullet.initialise(_initialLocation, _shooterVelocity, _imageLoader), Eq(true)); 
}

TEST_F(BulletTest, InitialisesWithFixedVelocityInSameDirectionAsShooter)
{
    EXPECT_THAT(_bullet.getVelocity(), Eq(Vector(Bullet::VELOCITY, 0)));
}

TEST_F(BulletTest, MovesWithConstantVelocity)
{
    _bullet.update(5);
    EXPECT_THAT(_bullet.getLocation(), Eq(Vector(_initialLocation.x + Bullet::VELOCITY*5,
                                                 _initialLocation.y)));
}

TEST_F(BulletTest, RendersImageAtCurrentLocation)
{
    _bullet.render();
    EXPECT_THAT(_testRenderable->renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}

TEST_F(BulletTest, HasBoundingBoxBasedOnScaledImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _bullet.getBoundingBox();
    float ratioLength = testLength*MovingObject::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}
