#ifndef _PJM_TESTSCREENWRAPPER_HPP_
#define _PJM_TESTSCREENWRAPPER_HPP_

#include <gmock/gmock.h>
#include <ScreenWrapper.hpp>

struct TestScreenWrapper : public pjm::ScreenWrapper
{
    TestScreenWrapper(const pjm::Vector& iBounds)
        : ScreenWrapper(iBounds)
    {}

    MOCK_CONST_METHOD3(wrap, void(pjm::Vector& ioLocation, 
                                  const pjm::Vector& iVelocity, 
                                  unsigned int iTimeElapsed));
};

#endif
