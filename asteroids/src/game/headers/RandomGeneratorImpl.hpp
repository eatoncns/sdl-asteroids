#ifndef _PJM_RANDOMGENERATORIMPL_HPP_
#define _PJM_RANDOMGENERATORIMPL_HPP_

#include <RandomGenerator.hpp>

namespace pjm
{
    class RandomGeneratorImpl : public RandomGenerator
    {
        float uniformAboutZero(float iRange);
    };
}

#endif
