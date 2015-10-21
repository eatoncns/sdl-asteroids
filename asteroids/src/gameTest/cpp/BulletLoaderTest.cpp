#include <BulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <gmock/gmock.h>

using namespace pjm;
using boost::shared_ptr;

class BulletLoaderTest : public ::testing::Test
{
    protected:
        BulletLoaderTest()
            : bulletLoader(imageLoader)
        {}

        TestImageLoader imageLoader;
        BulletLoader bulletLoader;
};

TEST_F(BulletLoaderTest, InterfaceCompiles)
{
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet();
}
