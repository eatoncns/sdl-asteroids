#ifndef _PJM_TESTBULLET_HPP_
#define _PJM_TESTBULLET_HPP_

#include <Bullet.hpp>
#include <Vector.hpp>

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


    pjm::Rectangle boundingBox;
};

#endif /* end of include guard: _PJM_TESTBULLET_HPP_ */
