#ifndef _PJM_TESTBULLETLOADER_HPP_
#define _PJM_TESTBULLETLOADER_HPP_

#include <BulletLoader.hpp>
#include <gmock/gmock.h>

struct TestBulletLoader : public pjm::BulletLoader
{
    TestBulletLoader()
    {
        ON_CALL(*this, loadBullet(::testing::_, ::testing::_))
            .WillByDefault(::testing::Return(boost::shared_ptr<pjm::Bullet>()));
    }

    MOCK_METHOD2(loadBullet, boost::shared_ptr<pjm::Bullet>(const pjm::Vector& iInitialLocation,
                                                            const double iAngle));
};

#endif /* end of include guard: _PJM_TESTBULLETLOADER_HPP_ */
