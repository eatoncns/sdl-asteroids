#ifndef _PJM_RENDERABLE_HPP_
#define _PJM_RENDERABLE_HPP_

namespace pjm
{
    struct Vector;

    struct Renderable
    {
        virtual void render(const Vector& iLocation) = 0;
        virtual int width() = 0;
        virtual int height() = 0;

        virtual ~Renderable() {}
    };
}

#endif
