#ifndef _SDL_TIMER_HPP_
#define _SDL_TIMER_HPP_

#include <Timer.hpp>

namespace pjm
{
    struct SDLTimer : public Timer
    {
        unsigned int getTime();
    };
}

#endif
