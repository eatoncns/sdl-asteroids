#include <gmock/gmock.h>
#include <GameLoop.hpp>
#include <Game.hpp>

using namespace pjm;
using ::testing::Eq;

struct TestGame : public Game
{
    TestGame()
        : iterations(0),
          updateCount(0)
    {}

    bool isRunning() { return (iterations-- > 0); }

    void update() { ++updateCount; }

    unsigned int iterations;
    unsigned int updateCount;
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
    EXPECT_THAT(game.updateCount, Eq(0));
}

TEST_F(GameLoopTest, UpdatesUntilGameIsStopped)
{
    game.iterations = 2;
    gameLoop.run();
    EXPECT_THAT(game.updateCount, Eq(2));
}
