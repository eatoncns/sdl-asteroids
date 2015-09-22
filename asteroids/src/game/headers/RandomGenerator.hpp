#ifndef _PJM_RANDOMGENERATOR_HPP_
#define _PJM_RANDOMGENERATOR_HPP_

namespace pjm
{
    struct RandomGenerator
    {
        virtual float uniformInRange(float iMin, float iMax) = 0;

        virtual ~RandomGenerator() {}
    };
}

#endif
