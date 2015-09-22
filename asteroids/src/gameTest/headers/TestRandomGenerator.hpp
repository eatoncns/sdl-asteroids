#ifndef _PJM_TESTRANDOMGENERATOR_HPP_
#define _PJM_TESTRANDOMGENERATOR_HPP_

#include <RandomGenerator.hpp>
#include <gmock/gmock.h>

struct TestRandomGenerator : pjm::RandomGenerator
{
    MOCK_METHOD2(uniformInRange, float(float iMin, float iMax));
};

#endif
