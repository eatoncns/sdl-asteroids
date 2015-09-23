#ifndef _PJM_TESTASTEROID_HPP_
#define _PJM_TESTASTEROID_HPP_

#include <Asteroid.hpp>
#include <list>

struct TestAsteroid : public pjm::Asteroid
{
    TestAsteroid(pjm::ImageLoader& iImageLoader, 
                 pjm::ScreenWrapper& iScreenWrapper,
                 pjm::RandomGenerator& iRandomGenerator);

    bool initialise(const pjm::Vector& iInitialLocation);

    void update(unsigned int iTimeElapsed);

    void render();

    int renderCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
};

#endif
