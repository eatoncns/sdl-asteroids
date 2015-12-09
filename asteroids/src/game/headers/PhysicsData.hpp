#ifndef _PJM_PHYSICSDATA_HPP_
#define _PJM_PHYSICSDATA_HPP_

#include <Vector.hpp>

namespace pjm
{
    struct PhysicsData
    {
        PhysicsData();

        void updateLocation(unsigned int iTimeElapsed);

        Vector location;
        Vector velocity;
    };
}

#endif /* end of include guard: _PJM_PHYSICSDATA_HPP_ */
