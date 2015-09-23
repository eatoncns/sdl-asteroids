#ifndef _PJM_TESTASTEROID_HPP_
#define _PJM_TESTASTEROID_HPP_

#include <Asteroid.hpp>
#include <ScreenWrapper.hpp>
#include <list>

struct TestAsteroid : public pjm::Asteroid
{
    TestAsteroid(pjm::ImageLoader& iImageLoader, 
                 pjm::RandomGenerator& iRandomGenerator);

    bool initialise(const pjm::Vector& iInitialLocation);

    void update(unsigned int iTimeElapsed);

    void render();

    int renderCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
    static pjm::ScreenWrapper screenWrapper;
};

#endif
