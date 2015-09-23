#ifndef _PJM_TESTSHIP_HPP_
#define _PJM_TESTSHIP_HPP_

#include <Ship.hpp>
#include <list>

struct TestShip : public pjm::Ship
{
    TestShip(pjm::ImageLoader& iImageLoader, pjm::ScreenWrapper& iScreenWrapper);

    bool initialise(const pjm::Vector& iInitialLocation);

    void update(const Action iAction, unsigned int iTimeElapsed);
    
    void render();

    int renderCalls;
    std::list<std::pair<Action, unsigned int> > updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
};

#endif
