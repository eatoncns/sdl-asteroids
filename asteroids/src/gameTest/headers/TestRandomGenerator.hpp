#ifndef _PJM_TESTRANDOMGENERATOR_HPP_
#define _PJM_TESTRANDOMGENERATOR_HPP_

#include <RandomGenerator.hpp>
#include <queue>

struct TestRandomGenerator : pjm::RandomGenerator
{
    float uniformAboutZero(float iRange)
    {
        float result = sequence.front();
        sequence.pop();
        return result;
    }

    std::queue<float> sequence;
};

#endif