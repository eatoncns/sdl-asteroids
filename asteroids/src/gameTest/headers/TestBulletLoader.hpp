#ifndef _PJM_TESTBULLETLOADER_HPP_
#define _PJM_TESTBULLETLOADER_HPP_

#include <BulletLoader.hpp>
#include <TestImageLoader.hpp>
#include <TestTimer.hpp>
#include <gmock/gmock.h>

struct TestBulletLoader : public pjm::BulletLoader
{
    TestBulletLoader(pjm::Timer& iTimer)
      : BulletLoader(pjm::Vector(0,0),
                     imageLoader,
                     iTimer)
    {
        ON_CALL(*this, loadBullet(::testing::_, ::testing::_))
            .WillByDefault(::testing::Return(boost::shared_ptr<pjm::FixedSpeedBullet>()));
    }

    MOCK_METHOD2(loadBullet, boost::shared_ptr<pjm::FixedSpeedBullet>(const pjm::Vector& iInitialLocation,
                                                            const double iAngle));

    static TestImageLoader imageLoader;
};

#endif /* end of include guard: _PJM_TESTBULLETLOADER_HPP_ */
