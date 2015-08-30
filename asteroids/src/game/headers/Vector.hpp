#ifndef _PJM_VECTOR_HPP_
#define _PJM_VECTOR_HPP_

#include <iostream>
#include <cmath> 

static const float TOL = 10E-6;

namespace pjm
{
    struct Vector
    {
        Vector(float iX, float iY)
            : x(iX), y(iY)
        {}

        bool operator==(const Vector& iOther) const
        {
            return (fabs(x-iOther.x) < TOL && 
                    fabs(y-iOther.y) < TOL);
        }

        bool operator!=(const Vector& iOther) const
        {
            return !(*this == iOther);
        }

        Vector& operator+=(const Vector& iRhs)
        {
            x += iRhs.x;
            y += iRhs.y;
            return *this;
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
