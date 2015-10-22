#ifndef _PJM_TESTTIMER_HPP_
#define _PJM_TESTTIMER_HPP_

#include <Timer.hpp>
#include <queue>

struct TestTimer : public pjm::Timer
{
    TestTimer()
    {}

    TestTimer(unsigned int iInitialTime)
    {
        times.push(iInitialTime);
    }

    unsigned int getTime()
    {
        unsigned int time  = times.front();
        times.pop();
        return time;
    }

    std::queue<unsigned int> times;
};

#endif /* end of include guard: _PJM_TESTTIMER_HPP_ */
