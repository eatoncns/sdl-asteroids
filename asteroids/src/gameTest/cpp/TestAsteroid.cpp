#include <TestAsteroid.hpp>

using namespace pjm;

TestAsteroid::TestAsteroid()
    : Asteroid(imageLoader, screenWrapper, random),
      renderCalls(0),
      initialiseSuccess(true),
      boundingBox(0,0,0,0)
{}


bool TestAsteroid::initialise(const Vector& iInitialLocation)
{
    initialiseCalls.push_back(iInitialLocation);
    return initialiseSuccess;
}


void TestAsteroid::update(unsigned int iTimeElapsed)
{
    updateCalls.push_back(iTimeElapsed);
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
ScreenWrapper TestAsteroid::screenWrapper(Vector(0,0));
TestRandomGenerator TestAsteroid::random;
