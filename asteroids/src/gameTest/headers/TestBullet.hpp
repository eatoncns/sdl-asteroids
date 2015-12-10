#ifndef _PJM_TESTBULLET_HPP_
#define _PJM_TESTBULLET_HPP_

#include <Bullet.hpp>
#include <Vector.hpp>
#include <Rectangle.hpp>
#include <list>
#include <gmock/gmock.h>

namespace pjm
{
    class Asteroid;
    struct ImageLoader;
}

struct TestBullet : public pjm::Bullet
{
    TestBullet()
        : boundingBox(0,0,0,0),
          renderCalls(0),
          expired(false)
    {}

    MOCK_METHOD3(initialise, bool(const pjm::Vector& iInitialLocation,
                                  const double iAngle,
                                  pjm::ImageLoader& iImageLoader));

    MOCK_METHOD1(update, void(unsigned int iTimeElapsed));

    pjm::Rectangle getBoundingBox()
    {
        return boundingBox;
    }

    void collideWith(pjm::Asteroid* iAsteroid)
    {
        collideCalls.push_back(iAsteroid);
    }

    bool isExpired()
    {
        return expired;
    }

    void render()
    {
        renderCalls++;
    }

    pjm::Rectangle boundingBox;
    int renderCalls;
    std::list<pjm::Asteroid*> collideCalls;
    bool expired;
};

#endif /* end of include guard: _PJM_TESTBULLET_HPP_ */
