#ifndef _PJM_GAME_HPP_
#define _PJM_GAME_HPP_

namespace pjm
{
    struct Game
    {
        virtual bool isRunning() = 0;
        virtual bool initialise() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif
