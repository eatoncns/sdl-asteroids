#ifndef _PJM_COLLIDABLE_OBJECT_HPP_
#define _PJM_COLLIDABLE_OBJECT_HPP_

#include <MovingObject.hpp>

namespace pjm
{
    class Rectangle;

    class CollidableObject : public MovingObject
    {
        public:
            virtual Rectangle getBoundingBox();

            const static float BOUNDING_BOX_RATIO;
    };
}

#endif
