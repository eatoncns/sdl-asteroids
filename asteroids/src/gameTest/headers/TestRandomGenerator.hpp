#ifndef _PJM_TESTRANDOMGENERATOR_HPP_
#define _PJM_TESTRANDOMGENERATOR_HPP_

#include <RandomGenerator.hpp>
#include <queue>

struct TestRandomGenerator : pjm::RandomGenerator
{
    float uniformInRange(float iMin, float iMax)
    {
        float result = sequence.front();
        sequence.pop();
        return result;
    }

    std::queue<float> sequence;
};

#endif
