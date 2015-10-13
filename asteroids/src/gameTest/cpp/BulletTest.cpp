#include <gmock/gmock.h>
#include <Bullet.hpp>
#include <MoveableObjectTest.hpp>

using namespace pjm;
using ::testing::Eq;

struct BulletSpy : public Bullet
{
    BulletSpy(const Vector& iBounds)
        : Bullet(iBounds)
    {}

    Vector& getVelocity()
    {
        return _velocity;
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
