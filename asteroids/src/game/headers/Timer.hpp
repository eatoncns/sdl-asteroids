#ifndef _PJM_TIMER_HPP_
#define _PJM_TIMER_HPP_

namespace pjm
{
    struct Timer
    {
        virtual unsigned int getTime() = 0;

        virtual ~Timer() {}
    };
}

#endif
