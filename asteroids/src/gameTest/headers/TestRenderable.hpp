#ifndef _PJM_TESTRENDERABLE_HPP_
#define _PJM_TESTRENDERABLE_HPP_

#include <Renderable.hpp>
#include <Vector.hpp>
#include <list>

struct TestRenderable : public pjm::Renderable
{
    void render(const pjm::Vector& iLocation, const double iAngle)
    {
        renderCalls.push_back(std::make_pair(iLocation, iAngle));
    }


    int width()
    {
        return 0;
    }

    int height()
    {
        return 0;
    }

    std::list<std::pair<pjm::Vector, double> > renderCalls;
};

#endif
