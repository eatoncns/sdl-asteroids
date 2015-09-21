#ifndef _PJM_LOCATIONGENERATOR_HPP_
#define _PJM_LOCATIONGENERATOR_HPP_

namespace pjm
{
    struct RandomGenerator;
    class Vector;

    class LocationGenerator
    {
        public:
            LocationGenerator(RandomGenerator& iRandom);

            virtual Vector generateLocation(float iMinDistanceFromOrigin,
                                            float iMaxDistanceFromOrigin);

        private:
            RandomGenerator& _random;
    };
}

#endif
