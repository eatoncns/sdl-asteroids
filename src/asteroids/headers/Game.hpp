#ifndef _PJM_GAME_HPP_
#define _PJM_GAME_HPP_

namespace pjm
{
    struct Game
    {
        virtual bool isRunning() = 0;
        virtual void update() = 0;
    };
}

#endif
