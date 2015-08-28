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


class GameLoopTest : public ::testing::Test
{
    protected:
        GameLoopTest()
            : gameLoop(game)
        {}

        TestGame game;
        GameLoop gameLoop;
};

TEST_F(GameLoopTest, DoesNothingWhenGameIsStopped)
{
    gameLoop.run();
    EXPECT_FALSE(game.updated);
}

TEST_F(GameLoopTest, RunsUpdateOnceBeforeGameIsStopped)
{
    game.running = true;
    gameLoop.run();
    EXPECT_TRUE(game.updated);
}
