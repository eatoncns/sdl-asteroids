#include <TestAsteroid.hpp>

using namespace pjm;

TestAsteroid::TestAsteroid(ImageLoader& iImageLoader, 
             ScreenWrapper& iScreenWrapper,
             RandomGenerator& iRandomGenerator)
    : Asteroid(iImageLoader, iScreenWrapper, iRandomGenerator),
      renderCalls(0),
      initialiseSuccess(true)
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


void TestAsteroid::render()
{
    ++renderCalls;
}
