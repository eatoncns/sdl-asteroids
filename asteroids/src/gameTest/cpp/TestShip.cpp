#include <TestShip.hpp>

using namespace pjm;

TestShip::TestShip(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper)
    : Ship(iImageLoader, iScreenWrapper),
          renderCalls(0),
          initialiseSuccess(true)
{}


bool TestShip::initialise(const Vector& iInitialLocation)
{
    initialiseCalls.push_back(iInitialLocation);
    return initialiseSuccess;
}


void TestShip::update(const Action iAction, unsigned int iTimeElapsed)
{
    updateCalls.push_back(std::make_pair(iAction, iTimeElapsed));
}
    

void TestShip::render()
{
    ++renderCalls;
}
