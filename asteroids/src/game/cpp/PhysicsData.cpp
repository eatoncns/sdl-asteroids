#include <PhysicsData.hpp>

namespace pjm
{
    PhysicsData::PhysicsData()
      : location(0, 0),
        velocity(0, 0)
     {}

     void PhysicsData::updateLocation(unsigned int iTimeElapsed)
     {
         location += velocity*iTimeElapsed;
     }
}
