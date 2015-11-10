#include <BulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <TestTimer.hpp>
#include <TestBullet.hpp>
#include <gmock/gmock.h>

using namespace pjm;
using boost::shared_ptr;
using ::testing::Return;
using ::testing::_;

class TestableBulletLoader : public BulletLoader
{
    public:
        TestableBulletLoader(const Vector& iBounds,
                             ImageLoader& iImageLoader,
                             Timer& iTimer,
                             shared_ptr<Bullet> iBullet)
          : BulletLoader(iBounds, iImageLoader, iTimer),
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
              shooterVelocity(2, 2),
              bullet(new TestBullet()),
              bulletLoader(bounds, imageLoader, timer, bullet)
        {}

        Vector bounds;
        TestImageLoader imageLoader;
        TestTimer timer;
        Vector initialLocation;
        Vector shooterVelocity;
        shared_ptr<TestBullet> bullet;
        TestableBulletLoader bulletLoader;
};

TEST_F(BulletLoaderTest, ReturnsInvalidWhenNotEnoughTimePassedSinceLastShot)
{
    timer.times.push(BulletLoader::RELOAD_TIME - 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet(initialLocation, shooterVelocity);
    EXPECT_FALSE(bullet);
}

TEST_F(BulletLoaderTest, ReturnsNewBulletWhenEnoughTimePassedSinceLastShot)
{
    ON_CALL(*bullet, initialise(_, _, _))
        .WillByDefault(Return(true));
    timer.times.push(BulletLoader::RELOAD_TIME + 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet(initialLocation, shooterVelocity);
    EXPECT_TRUE(bullet);
}

TEST_F(BulletLoaderTest, ReturnsInvalidWhenBulletInitialisationFails)
{
    ON_CALL(*bullet, initialise(_, _, _))
        .WillByDefault(Return(false));
    timer.times.push(BulletLoader::RELOAD_TIME + 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet(initialLocation, shooterVelocity);
}

TEST_F(BulletLoaderTest, InitialisesLoadedBulletLocation)
{
    EXPECT_CALL(*bullet, initialise(initialLocation, _, _))
        .WillOnce(Return(true));
    timer.times.push(BulletLoader::RELOAD_TIME + 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet(initialLocation, shooterVelocity);
}

TEST_F(BulletLoaderTest, InitialisesLoadedBulletShooterVelocity)
{
    EXPECT_CALL(*bullet, initialise(_, shooterVelocity, _))
        .WillOnce(Return(true));
    timer.times.push(BulletLoader::RELOAD_TIME + 1);
    shared_ptr<Bullet> bullet = bulletLoader.loadBullet(initialLocation, shooterVelocity);
}
