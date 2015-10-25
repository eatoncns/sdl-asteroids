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
            : bounds(5, 5),
              timer(0),
              bulletLoader(bounds, imageLoader, timer)
        {}

        Vector bounds;
        TestImageLoader imageLoader;
        TestTimer timer;
        BulletLoader bulletLoader;
};

TEST_F(BulletLoaderTest, ReturnsInvalidWhenNotEnoughTimePassedSinceLastShot)
{
    timer.times.push(BulletLoader::RELOAD_TIME - 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet();
    EXPECT_FALSE(bullet);
}

TEST_F(BulletLoaderTest, ReturnsNewBulletWhenEnoughTimePassedSinceLastShot)
{
    timer.times.push(BulletLoader::RELOAD_TIME + 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet();
    EXPECT_TRUE(bullet);
}
