#include <BulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <TestTimer.hpp>
#include <gmock/gmock.h>

using namespace pjm;
using boost::shared_ptr;

class BulletLoaderTest : public ::testing::Test
{
    protected:
        BulletLoaderTest()
            : timer(0),
              bulletLoader(imageLoader, timer)
        {}

        TestImageLoader imageLoader;
        TestTimer timer;
        BulletLoader bulletLoader;
};

TEST_F(BulletLoaderTest, ReturnsInvalidWhenNotEnoughTimePassedSinceLastShot)
{

    shared_ptr<Bullet> bullet = bulletLoader.loadBullet();
}
