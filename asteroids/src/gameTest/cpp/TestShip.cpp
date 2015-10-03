#include <TestShip.hpp>

using namespace pjm;
using boost::shared_ptr;

TestShip::TestShip()
    : Ship(screenWrapper),
          renderCalls(0),
          initialiseSuccess(true),
          boundingBox(0,0,0,0)
{}


bool TestShip::initialise(const Vector& iInitialLocation,
                          ImageLoader& iImageLoader)
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


shared_ptr<ScreenWrapper> TestShip::screenWrapper;
TestImageLoader TestShip::imageLoader;
