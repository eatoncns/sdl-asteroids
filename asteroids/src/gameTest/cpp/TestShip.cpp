#include <TestShip.hpp>

using namespace pjm;

TestShip::TestShip()
    : Ship(imageLoader, screenWrapper),
          renderCalls(0),
          initialiseSuccess(true),
          boundingBox(0,0,0,0)
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


Rectangle TestShip::getBoundingBox()
{
    return boundingBox;
}
    

void TestShip::render()
{
    ++renderCalls;
}


TestImageLoader TestShip::imageLoader;
ScreenWrapper TestShip::screenWrapper(Vector(0,0));
