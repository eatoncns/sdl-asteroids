#include <gmock/gmock.h>
#include <GameLoop.hpp>
#include <Game.hpp>
#include <list>
#include <string>

using namespace pjm;
using ::testing::Eq;
using ::testing::ElementsAre;

struct TestGame : public Game
{
    TestGame()
        : iterations(0),
          updateCount(0)
    {}

    bool isRunning()
    {
        return (iterations-- > 0);
    }

    void update()
    {
        calls.push_back("update");
        ++updateCount;
    }

    void draw()
    {
        calls.push_back("draw");
    }

    unsigned int iterations;
    unsigned int updateCount;
    std::list<std::string> calls;
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

TEST_F(GameLoopTest, CallsDrawAfterUpdate)
{
    game.iterations = 1;
    gameLoop.run();
    EXPECT_THAT(game.calls, ElementsAre("update", "draw"));
}
