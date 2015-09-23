#ifndef _PJM_TESTLOCATIONGENERATOR_HPP_
#define _PJM_TESTLOCATIONGENERATOR_HPP_

#include <LocationGenerator.hpp>

struct TestLocationGenerator : public pjm::LocationGenerator
{
    TestLocationGenerator(const pjm::ScreenInfo& iScreenInfo,
                          pjm::RandomGenerator& iRandom)
        : LocationGenerator(iScreenInfo, iRandom)
    {}

    pjm::Vector generateLocation(float iMinDistanceFromOrigin,
                                 float iMaxDistanceFromOrigin)
    {
        return pjm::Vector(7.7, 3.4);  
    }
};

#endif
