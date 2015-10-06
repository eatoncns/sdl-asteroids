#ifndef _PJM_TESTCOLLISIONINTERACTIONS_HPP_
#define _PJM_TESTCOLLISIONINTERACTIONS_HPP_

#include <CollisionInteractions.hpp>

struct TestCollisionInteractions : public pjm::CollisionInteractions
{
    TestCollisionInteractions()
        : CollisionInteractions(boost::shared_ptr<pjm::Ship>(),
                                _asteroids),
          updateCalls(0),
          shipCollision(false)
    {}

    bool update()
    {
        updateCalls++;
        return shipCollision;
    }

    int updateCalls;
    bool shipCollision;

    std::list<boost::shared_ptr<pjm::Asteroid> > _asteroids;
};

#endif
