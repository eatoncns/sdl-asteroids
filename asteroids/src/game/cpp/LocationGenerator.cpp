#include <LocationGenerator.hpp>
#include <RandomGenerator.hpp>
#include <Vector.hpp>

namespace pjm
{
    LocationGenerator::LocationGenerator(const ScreenInfo& iScreenInfo, 
                                         RandomGenerator& iRandom)
        : _screenInfo(iScreenInfo),
          _random(iRandom)
    {}

    Vector LocationGenerator::generateLocation(float iMinDistanceFromOrigin,
                                               float iMaxDistanceFromOrigin)
    {
        return Vector(100, 100);
    }
}
