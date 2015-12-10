#ifndef _PJM_TESTASTEROID_HPP_
#define _PJM_TESTASTEROID_HPP_

#include <Asteroid.hpp>
#include <TestImageLoader.hpp>
#include <TestRandomGenerator.hpp>
#include <ScreenWrapper.hpp>
#include <Rectangle.hpp>
#include <Vector.hpp>
#include <list>

struct TestAsteroid : public pjm::Asteroid
{
    TestAsteroid();

    bool initialise(const pjm::Vector& iInitialLocation,
                    pjm::ImageLoader& iImageLoader,
                    pjm::RandomGenerator& iRandomGenerator);

    void update(unsigned int iTimeElapsed);

    void collideWith(pjm::Asteroid* iOther);
    void collideWith(pjm::Bullet* iBullet);

    bool isExpired();

    pjm::Rectangle getBoundingBox();

    void render();

    pjm::Vector getNormalisedDirection();
    void setNormalisedDirection(const pjm::Vector& iNormalisedDirection);

    int renderCalls;
    std::list<pjm::Asteroid*> collideCalls;
    std::list<pjm::Bullet*> bulletCollideCalls;
    std::list<unsigned int> updateCalls;
    std::list<pjm::Vector> initialiseCalls;
    bool initialiseSuccess;
    bool expired;
    pjm::Rectangle boundingBox;
    pjm::Vector normalisedDirection;
    std::list<pjm::Vector> setNormalisedDirectionCalls;
};

#endif
