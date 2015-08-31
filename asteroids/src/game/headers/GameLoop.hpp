#ifndef _PJM_GAMELOOP_HPP_
#define _PJM_GAMELOOP_HPP_

namespace pjm
{
    class Game;
    class Timer;

    class GameLoop
    {
        public:
            GameLoop(Game& iGame, Timer& iTimer);

            bool run();

        private:
            Game& _game;
            Timer& _timer;
    };
}

#endif
