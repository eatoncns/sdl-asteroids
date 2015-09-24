#ifndef _PJM_RECTANGLE_HPP_
#define _PJM_RECTANGLE_HPP_

namespace pjm
{
    struct Rectangle
    {
        Rectangle(float iX, float iY, float iWidth, float iHeight)
            : x(iX), y(iY), w(iWidth), h(iHeight)
        {}

        float x;
        float y;
        float w;
        float h;
    };
}

#endif
