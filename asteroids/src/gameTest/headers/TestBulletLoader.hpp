#ifndef _PJM_TESTBULLETLOADER_HPP_
#define _PJM_TESTBULLETLOADER_HPP_

#include <BulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <TestTimer.hpp>

struct TestBulletLoader : public pjm::BulletLoader
{
    TestBulletLoader()
      : BulletLoader(pjm::Vector(0,0),
                     imageLoader,
                     timer),
        loadCalls(0)
     {}

    boost::shared_ptr<pjm::Bullet> loadBullet()
    {
        loadCalls++;
        return boost::shared_ptr<pjm::Bullet>();
    }

    static TestImageLoader imageLoader;
    static TestTimer timer;
    int loadCalls;
};

#endif /* end of include guard: _PJM_TESTBULLETLOADER_HPP_ */
