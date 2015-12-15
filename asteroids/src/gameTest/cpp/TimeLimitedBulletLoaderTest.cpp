#include <TimeLimitedBulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <TestTimer.hpp>
#include <TestBullet.hpp>
#include <gmock/gmock.h>

using namespace pjm;
using boost::shared_ptr;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::_;

class TestableBulletLoader : public TimeLimitedBulletLoader
{
    public:
        TestableBulletLoader(const Vector& iBounds,
                             ImageLoader& iImageLoader,
                             Timer& iTimer,
                             shared_ptr<Bullet> iBullet)
          : TimeLimitedBulletLoader(iBounds, iImageLoader, iTimer),
            bullet(iBullet)
        {}

    private:
        boost::shared_ptr<Bullet> makeBullet()
        {
            return bullet;
        }

    shared_ptr<Bullet> bullet;
};

class BulletLoaderTest : public ::testing::Test
{
    protected:
        BulletLoaderTest()
            : bounds(5, 5),
              timer(0),
              initialLocation(1, 1),
              angle(0.0),
              bullet(new NiceMock<TestBullet>()),
              bulletLoader(bounds, imageLoader, timer, bullet)
        {}

        shared_ptr<Bullet> load(int iReloadTimeOffset)
        {
            timer.times.push(TimeLimitedBulletLoader::RELOAD_TIME + iReloadTimeOffset);
            return bulletLoader.loadBullet(initialLocation, angle);
        }

        Vector bounds;
        TestImageLoader imageLoader;
        TestTimer timer;
        Vector initialLocation;
        double angle;
        shared_ptr<NiceMock<TestBullet> > bullet;
        TestableBulletLoader bulletLoader;
};

TEST_F(BulletLoaderTest, ReturnsInvalidWhenNotEnoughTimePassedSinceLastShot)
{
    shared_ptr<Bullet> result = load(-1);
    EXPECT_FALSE(result);
}

TEST_F(BulletLoaderTest, ReturnsNewBulletWhenEnoughTimePassedSinceLastShot)
{
    ON_CALL(*bullet, initialise(_, _, _))
        .WillByDefault(Return(true));
    shared_ptr<Bullet> result = load(1);
    EXPECT_TRUE(result);
}

TEST_F(BulletLoaderTest, ReturnsInvalidWhenBulletInitialisationFails)
{
    ON_CALL(*bullet, initialise(_, _, _))
        .WillByDefault(Return(false));
    shared_ptr<Bullet> result = load(1);
    EXPECT_FALSE(result);
}

TEST_F(BulletLoaderTest, InitialisesLoadedBulletLocation)
{
    EXPECT_CALL(*bullet, initialise(initialLocation, _, _))
        .WillOnce(Return(true));
    load(1);
}

TEST_F(BulletLoaderTest, InitialisesLoadedBulletAngle)
{
    EXPECT_CALL(*bullet, initialise(_, angle, _))
        .WillOnce(Return(true));
    load(1);
}
