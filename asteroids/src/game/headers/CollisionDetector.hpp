#ifndef _PJM_COLLISIONDETECTOR_HPP_
#define _PJM_COLLISIONDETECTOR_HPP_

namespace pjm
{
    struct Rectangle;

    struct CollisionDetector
    {
        virtual bool areColliding(const Rectangle& iA, const Rectangle& iB) const;

        virtual ~CollisionDetector() {}
    };
}

#endif
