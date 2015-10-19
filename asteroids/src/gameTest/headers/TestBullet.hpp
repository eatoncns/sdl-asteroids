#ifndef _PJM_TESTBULLET_HPP_
#define _PJM_TESTBULLET_HPP_

#include <Bullet.hpp>
#include <Vector.hpp>

namespace pjm
{
    class Asteroid;
}

struct TestBullet : public pjm::Bullet
{
    TestBullet()
        : Bullet(pjm::Vector(1,1)),
          boundingBox(0,0,0,0)
    {}

    pjm::Rectangle getBoundingBox()
    {
        return boundingBox;
    }

    void collideWith(pjm::Asteroid* iAsteroid)
    {
        collideCalls.push_back(iAsteroid);
    }


    pjm::Rectangle boundingBox;
    std::list<pjm::Asteroid*> collideCalls;
};

#endif /* end of include guard: _PJM_TESTBULLET_HPP_ */
