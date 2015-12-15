#ifndef _PJM_TESTLOCATIONGENERATOR_HPP_
#define _PJM_TESTLOCATIONGENERATOR_HPP_

#include <LocationGenerator.hpp>
#include <Vector.hpp>

struct TestLocationGenerator : public pjm::LocationGenerator
{
    pjm::Vector generateLocation(float iMinDistanceFromOrigin,
                                 float iMaxDistanceFromOrigin)
    {
        return pjm::Vector(x, y);
    }

    static float x;
    static float y;
};

#endif
