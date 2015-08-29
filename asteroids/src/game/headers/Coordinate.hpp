#ifndef _PJM_COORDINATE_HPP_
#define _PJM_COORDINATE_HPP_

#include <iostream>

namespace pjm
{
    struct Coordinate
    {
        Coordinate(int iX, int iY)
            : x(iX), y(iY)
        {}

        bool operator==(const Coordinate& iOther) const
        {
            return (x == iOther.x && y == iOther.y);
        }
        
        friend std::ostream& operator<<(std::ostream& iOS, 
                                        const Coordinate& iCoordinate)
        {
            return (iOS <<  "(" << iCoordinate.x << "," << iCoordinate.y << ")");
        }

        int x;
        int y;
    };

}

#endif
