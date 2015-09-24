#ifndef _PJM_TESTLOCATIONGENERATOR_HPP_
#define _PJM_TESTLOCATIONGENERATOR_HPP_

#include <LocationGenerator.hpp>
#include <ScreenInfo.hpp>
#include <TestRandomGenerator.hpp>
#include <Vector.hpp>

struct TestLocationGenerator : public pjm::LocationGenerator
{
    TestLocationGenerator()
        : LocationGenerator(screenInfo, random)
    {}

    pjm::Vector generateLocation(float iMinDistanceFromOrigin,
                                 float iMaxDistanceFromOrigin)
    {
        return pjm::Vector(x, y);  
    }

    static float x;
    static float y;
    static pjm::ScreenInfo screenInfo;
    static TestRandomGenerator random;
};

#endif
