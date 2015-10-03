#include <TestAsteroid.hpp>

using namespace pjm;
using boost::shared_ptr;

TestAsteroid::TestAsteroid()
    : Asteroid(screenWrapper),
      renderCalls(0),
      initialiseSuccess(true),
      boundingBox(0,0,0,0)
{}


bool TestAsteroid::initialise(const Vector& iInitialLocation,
                              ImageLoader& iImageLoader,
                              RandomGenerator& iRandomGenerator)
{
    initialiseCalls.push_back(iInitialLocation);
    return initialiseSuccess;
}


void TestAsteroid::update(unsigned int iTimeElapsed)
{
    updateCalls.push_back(iTimeElapsed);
}


void TestAsteroid::collideWith(Asteroid* iOther)
{
    collideCalls.push_back(iOther);
}


Rectangle TestAsteroid::getBoundingBox()
{
    return boundingBox;
}


void TestAsteroid::render()
{
    ++renderCalls;
}

TestImageLoader TestAsteroid::imageLoader;
shared_ptr<ScreenWrapper> TestAsteroid::screenWrapper;
