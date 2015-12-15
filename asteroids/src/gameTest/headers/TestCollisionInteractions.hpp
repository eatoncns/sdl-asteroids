#ifndef _PJM_TESTCOLLISIONINTERACTIONS_HPP_
#define _PJM_TESTCOLLISIONINTERACTIONS_HPP_

#include <CollisionInteractions.hpp>

struct TestCollisionInteractions : public pjm::CollisionInteractions
{
    TestCollisionInteractions()
        : updateCalls(0)
    {}

    void update()
    {
        updateCalls++;
    }

    int updateCalls;
};

#endif
