#ifndef _PJM_LOCATIONGENERATOR_HPP_
#define _PJM_LOCATIONGENERATOR_HPP_

#include <ScreenInfo.hpp>

namespace pjm
{
    struct RandomGenerator;
    class Vector;

    class LocationGenerator
    {
        public:
            LocationGenerator(const ScreenInfo& iScreenInfo, RandomGenerator& iRandom);

            virtual Vector generateLocation(float iMinDistanceFromOrigin,
                                            float iMaxDistanceFromOrigin);

        private:
            ScreenInfo _screenInfo;
            RandomGenerator& _random;
    };
}

#endif
