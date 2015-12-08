#include <TestShip.hpp>

using namespace pjm;
using boost::shared_ptr;

TestShip::TestShip()
    : Ship(screenWrapper, bulletLoader),
      renderCalls(0),
      initialiseSuccess(true),
      expired(false),
      boundingBox(0,0,0,0)
{}


void TestShip::willShootBullet(shared_ptr<Bullet> iBullet)
{
    _bullet = iBullet;
}


bool TestShip::initialise(const Vector& iInitialLocation,
                          ImageLoader& iImageLoader)
{
    initialiseCalls.push_back(iInitialLocation);
    return initialiseSuccess;
}


shared_ptr<Bullet> TestShip::update(const ShipAction& iAction,
                                    unsigned int iTimeElapsed)
{
    return _bullet;
}


Rectangle TestShip::getBoundingBox()
{
    return boundingBox;
}


void TestShip::render()
{
    ++renderCalls;
}


void TestShip::collideWith(pjm::Asteroid* iAsteroid)
{
    collideCalls.push_back(iAsteroid);
}


bool TestShip::isExpired()
{
    return expired;
}


shared_ptr<ScreenWrapper> TestShip::screenWrapper;
shared_ptr<BulletLoader> TestShip::bulletLoader;
TestImageLoader TestShip::imageLoader;
