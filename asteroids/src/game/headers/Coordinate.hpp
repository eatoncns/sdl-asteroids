#ifndef _PJM_COORDINATE_HPP_
#define _PJM_COORDINATE_HPP_

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

        int x;
        int y;
    };
}

#endif
