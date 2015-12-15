#ifndef _PJM_LOCATIONGENERATOR_HPP_
#define _PJM_LOCATIONGENERATOR_HPP_

namespace pjm
{
    class Vector;

    struct LocationGenerator
    {
        virtual Vector generateLocation(float iMinDistanceFromCentre,
                                        float iMaxDistanceFromCentre) = 0;

        virtual ~LocationGenerator() {}
    };
}

#endif /* end of include guard: _PJM_LOCATIONGENERATOR_HPP_ */
