#ifndef _PJM_BOOSTRANDOMGENERATOR_HPP_
#define _PJM_BOOSTRANDOMGENERATOR_HPP_

#include <RandomGenerator.hpp>

namespace pjm
{
    class BoostRandomGenerator : public RandomGenerator
    {
        float uniformInRange(float iMin, float iMax);
    };
}

#endif
