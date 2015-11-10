#include <TestShip.hpp>

using namespace pjm;
using boost::shared_ptr;

TestShip::TestShip()
    : Ship(screenWrapper),
          renderCalls(0),
          initialiseSuccess(true),
          expired(false),
          boundingBox(0,0,0,0)
{}


bool TestShip::initialise(const Vector& iInitialLocation,
                          ImageLoader& iImageLoader)
{
    initialiseCalls.push_back(iInitialLocation);
    return initialiseSuccess;
}


shared_ptr<Bullet> TestShip::update(const ShipAction& iAction,
                                    unsigned int iTimeElapsed)
{
    return bullet;
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
TestImageLoader TestShip::imageLoader;
