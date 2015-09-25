#ifndef _PJM_TESTASTEROID_HPP_
#define _PJM_TESTASTEROID_HPP_

#include <Asteroid.hpp>
#include <TestImageLoader.hpp>
#include <TestRandomGenerator.hpp>
#include <ScreenWrapper.hpp>
#include <Rectangle.hpp>
#include <list>

struct TestAsteroid : public pjm::Asteroid
{
    TestAsteroid();

    bool initialise(const pjm::Vector& iInitialLocation);

    void update(unsigned int iTimeElapsed);

    pjm::Rectangle getBoundingBox();

    void render();

    int renderCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
    pjm::Rectangle boundingBox;
    static TestImageLoader imageLoader;
    static pjm::ScreenWrapper screenWrapper;
    static TestRandomGenerator random;
};

#endif
