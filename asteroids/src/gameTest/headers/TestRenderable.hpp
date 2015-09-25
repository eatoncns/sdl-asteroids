#ifndef _PJM_TESTRENDERABLE_HPP_
#define _PJM_TESTRENDERABLE_HPP_

#include <Renderable.hpp>
#include <Vector.hpp>
#include <list>

struct TestRenderable : public pjm::Renderable
{
    TestRenderable()
        : w(0),
          h(0)
    {}

    void render(const pjm::Vector& iLocation, const double iAngle)
    {
        renderCalls.push_back(std::make_pair(iLocation, iAngle));
    }

    int width()
    {
        return w;
    }

    int height()
    {
        return h;
    }

    std::list<std::pair<pjm::Vector, double> > renderCalls;
    int w;
    int h;
};

#endif
