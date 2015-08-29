#ifndef _PJM_TESTRENDERABLE_HPP_
#define _PJM_TESTRENDERABLE_HPP_

#include <Renderable.hpp>
#include <Coordinate.hpp>
#include <list>

struct TestRenderable : public pjm::Renderable
{
    void render(pjm::Coordinate iLocation)
    {
        renderCalls.push_back(iLocation);
    }

    std::list<pjm::Coordinate> renderCalls;
};

#endif
