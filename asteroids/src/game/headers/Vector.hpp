#ifndef _PJM_VECTOR_HPP_
#define _PJM_VECTOR_HPP_

#include <iostream>

namespace pjm
{
    struct Vector
    {
        Vector(float iX, float iY)
            : x(iX), y(iY)
        {}

        bool operator==(const Vector& iOther) const
        {
            return (x == iOther.x && y == iOther.y);
        }
        
        friend std::ostream& operator<<(std::ostream& iOS, 
                                        const Vector& iVector)
        {
            return (iOS <<  "(" << iVector.x << "," << iVector.y << ")");
        }

        float x;
        float y;
    };

}

#endif
