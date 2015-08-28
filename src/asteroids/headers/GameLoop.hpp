#ifndef _PJM_GAMELOOP_HPP_
#define _PJM_GAMELOOP_HPP_

namespace pjm
{
    class Game;

    class GameLoop
    {
        public:
            explicit GameLoop(Game& iGame);

            void run();

        private:
            Game& _game;
    };
}

#endif
