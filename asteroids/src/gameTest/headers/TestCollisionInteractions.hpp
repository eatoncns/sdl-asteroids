#ifndef _PJM_TESTCOLLISIONINTERACTIONS_HPP_
#define _PJM_TESTCOLLISIONINTERACTIONS_HPP_

#include <CollisionInteractions.hpp>

struct TestCollisionInteractions : public pjm::CollisionInteractions
{
    TestCollisionInteractions()
        : CollisionInteractions(boost::shared_ptr<pjm::Ship>(),
                                _asteroids,
                                _bullets),
          updateCalls(0)
    {}

    void update()
    {
        updateCalls++;
    }

    int updateCalls;

    std::list<boost::shared_ptr<pjm::Asteroid> > _asteroids;
    std::list<boost::shared_ptr<pjm::Bullet> > _bullets;
};

#endif
