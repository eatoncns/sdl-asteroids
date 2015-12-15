#ifndef _PJM_RANDOMLOCATIONGENERATOR_HPP_
#define _PJM_RANDOMLOCATIONGENERATOR_HPP_

#include <LocationGenerator.hpp>
#include <ScreenInfo.hpp>

namespace pjm
{
    struct RandomGenerator;
    class Vector;

    class RandomLocationGenerator : public LocationGenerator
    {
        public:
            RandomLocationGenerator(const ScreenInfo& iScreenInfo, RandomGenerator& iRandom);

            Vector generateLocation(float iMinDistanceFromCentre,
                                    float iMaxDistanceFromCentre);

        private:
            ScreenInfo _screenInfo;
            RandomGenerator& _random;
    };
}

#endif
