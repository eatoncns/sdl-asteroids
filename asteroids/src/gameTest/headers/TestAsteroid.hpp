#ifndef _PJM_TESTASTEROID_HPP_
#define _PJM_TESTASTEROID_HPP_

#include <Asteroid.hpp>
#include <list>

struct TestAsteroid : public pjm::Asteroid
{
    TestAsteroid(pjm::ImageLoader& iImageLoader, 
                 pjm::ScreenWrapper& iScreenWrapper,
                 pjm::RandomGenerator& iRandomGenerator)
        : Asteroid(iImageLoader, iScreenWrapper, iRandomGenerator),
          renderCalls(0),
          initialiseSuccess(true)
    {}

    bool initialise(const pjm::Vector& iInitialLocation)
    {
        initialiseCalls.push_back(iInitialLocation);
        return initialiseSuccess;
    }

    void update(unsigned int iTimeElapsed)
    {
        updateCalls.push_back(iTimeElapsed);
    }

    void render()
    {
        ++renderCalls;
    }

    int renderCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
};

#endif
