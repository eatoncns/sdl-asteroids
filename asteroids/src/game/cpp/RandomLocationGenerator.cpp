#include <RandomLocationGenerator.hpp>
#include <RandomGenerator.hpp>
#include <Vector.hpp>
#include <math.h>

namespace pjm
{
    RandomLocationGenerator::RandomLocationGenerator(const ScreenInfo& iScreenInfo,
                                                     RandomGenerator& iRandom)
        : _screenInfo(iScreenInfo),
          _random(iRandom)
    {}

    Vector RandomLocationGenerator::generateLocation(float iMinDistanceFromCentre,
                                                     float iMaxDistanceFromCentre)
    {
        Vector centre(_screenInfo.width/2, _screenInfo.height/2);
        float angle = _random.uniformInRange(0,1) * 2 * M_PI;
        Vector direction (sin(angle), -cos(angle));
        float distance = _random.uniformInRange(iMinDistanceFromCentre, iMaxDistanceFromCentre);
        Vector location = centre + (direction*distance);
        return location;
    }
}
