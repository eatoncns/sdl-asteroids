#include <gmock/gmock.h>
#include <Bullet.hpp>
#include <MoveableObjectTest.hpp>

using namespace pjm;

class BulletTest : public MoveableObjectTest
{
    protected:
        BulletTest()
            : _bounds(200, 200),
              _shooterVelocity(1, 1),
              _bullet(_bounds)

        {
            _bullet.initialise(_initialLocation, _shooterVelocity, _imageLoader);
        }

        Vector _bounds;
        Vector _shooterVelocity;
        Bullet _bullet;
};


TEST_F(BulletTest, InterfaceCompiles)
{

}
