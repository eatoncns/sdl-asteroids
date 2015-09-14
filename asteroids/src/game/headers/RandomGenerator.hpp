#ifndef _PJM_RANDOMGENERATOR_HPP_
#define _PJM_RANDOMGENERATOR_HPP_

namespace pjm
{
    struct RandomGenerator
    {
        virtual float uniformAboutZero(float iRange) = 0;

        virtual ~RandomGenerator() {}
    };
}

#endif
