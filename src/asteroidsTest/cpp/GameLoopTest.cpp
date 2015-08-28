#include <gmock/gmock.h>
#include <GameLoop.hpp>
#include <Game.hpp>

using namespace pjm;

struct TestGame : public Game
{
    TestGame()
        : running(false),
          updated(false)
    {}

    bool isRunning() { return running; }
    void update() { updated = true; }

    bool running;
    bool updated;
};

TEST(GameLoopTest, DoesNothingWhenGameIsStopped)
{
    TestGame game;
    GameLoop gameLoop(game);
    gameLoop.run();
    EXPECT_FALSE(game.updated);
}

TEST(GameLoopTest, RunsUpdateOnceBeforeGameIsStopped)
{
    TestGame game;
    game.running = true;
    GameLoop gameLoop(game);
    gameLoop.run();
    EXPECT_TRUE(game.updated);
}
