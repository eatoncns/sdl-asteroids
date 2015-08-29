#ifndef _PJM_RENDERABLE_HPP_
#define _PJM_RENDERABLE_HPP_

#include <Coordinate.hpp>

namespace pjm
{
    struct Renderable
    {
        virtual void render(Coordinate iLocation) = 0;
        virtual ~Renderable() {}
    };
}

#endif
