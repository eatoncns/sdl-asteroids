#ifndef _PJM_COLLISIONINTERACTIONS_HPP_
#define _PJM_COLLISIONINTERACTIONS_HPP_

namespace pjm
{
    struct CollisionInteractions
    {
        virtual void update() = 0;

        virtual ~CollisionInteractions() {}
    };
}

#endif /* end of include guard: _PJM_COLLISIONINTERACTIONS_HPP_ */
