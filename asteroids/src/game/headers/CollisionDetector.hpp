#ifndef _PJM_COLLISIONDETECTOR_HPP_
#define _PJM_COLLISIONDETECTOR_HPP_

namespace pjm
{
    struct Rectangle;

    struct CollisionDetector
    {
        bool areColliding(const Rectangle& iLhs, const Rectangle& iRhs);
    };
}

#endif
