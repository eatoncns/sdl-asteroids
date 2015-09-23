#ifndef _PJM_TESTSHIP_HPP_
#define _PJM_TESTSHIP_HPP_

#include <Ship.hpp>
#include <list>

struct TestShip : public pjm::Ship
{
    TestShip(pjm::ImageLoader& iImageLoader, pjm::ScreenWrapper& iScreenWrapper)
        : Ship(iImageLoader, iScreenWrapper),
          renderCalls(0),
          initialiseSuccess(true)
    {}

    bool initialise(const pjm::Vector& iInitialLocation)
    {
        initialiseCalls.push_back(iInitialLocation);
        return initialiseSuccess;
    }

    void update(const Action iAction, unsigned int iTimeElapsed)
    {
        updateCalls.push_back(std::make_pair(iAction, iTimeElapsed));
    }

    void render()
    {
        ++renderCalls;
    }

    int renderCalls;
    std::list<std::pair<Action, unsigned int> > updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
};

#endif
