#ifndef _PJM_TESTSHIP_HPP_
#define _PJM_TESTSHIP_HPP_

#include <Ship.hpp>
#include <ScreenWrapper.hpp>
#include <TestImageLoader.hpp>
#include <Rectangle.hpp>
#include <list>

struct TestShip : public pjm::Ship
{
    TestShip();

    bool initialise(const pjm::Vector& iInitialLocation);

    void update(const Action iAction, unsigned int iTimeElapsed);

    pjm::Rectangle getBoundingBox();
    
    void render();

    int renderCalls;
    std::list<std::pair<Action, unsigned int> > updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
    pjm::Rectangle boundingBox;
    static TestImageLoader imageLoader;
    static pjm::ScreenWrapper screenWrapper;
};

#endif
