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

    bool initialise(const pjm::Vector& iInitialLocation,
                    pjm::ImageLoader& iImageLoader,
                    pjm::RandomGenerator& iRandomGenerator);

    void update(unsigned int iTimeElapsed);

    void collideWith(Asteroid* iOther);

    pjm::Rectangle getBoundingBox();

    void render();

    int renderCalls;
    std::list<Asteroid*> collideCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
    pjm::Rectangle boundingBox;
    static TestImageLoader imageLoader;
    static boost::shared_ptr<pjm::ScreenWrapper> screenWrapper;
};

#endif
