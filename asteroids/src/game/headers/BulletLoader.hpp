#ifndef _PJM_BULLETLOADER_HPP_
#define _PJM_BULLETLOADER_HPP_

#include <boost/shared_ptr.hpp>

namespace pjm
{
    class Bullet;
    class Vector;

    struct BulletLoader
    {

        virtual boost::shared_ptr<Bullet> loadBullet(const Vector& iInitialLocation,
                                                     const double iAngle) = 0;
    };
}

#endif /* end of include guard: _PJM_BULLETLOADER_HPP_ */
