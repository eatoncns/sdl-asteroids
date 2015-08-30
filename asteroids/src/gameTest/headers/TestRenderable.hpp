#ifndef _PJM_TESTRENDERABLE_HPP_
#define _PJM_TESTRENDERABLE_HPP_

#include <Renderable.hpp>
#include <Vector.hpp>
#include <list>

struct TestRenderable : public pjm::Renderable
{
    void render(const pjm::Vector& iLocation)
    {
        renderCalls.push_back(iLocation);
    }


    int width()
    {
        return 0;
    }

    int height()
    {
        return 0;
    }

    std::list<pjm::Vector> renderCalls;
};

#endif
