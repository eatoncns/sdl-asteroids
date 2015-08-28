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

    void initialise()
    {
        calls.push_back("init");
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

        void runIterations(const unsigned int iIterations)
        {
            game.iterations = iIterations;
            gameLoop.run();
        }

        TestGame game;
        GameLoop gameLoop;
};

TEST_F(GameLoopTest, DoesNothingWhenGameIsStopped)
{
    runIterations(0);
    EXPECT_THAT(game.updateCount, Eq(0));
}

TEST_F(GameLoopTest, UpdatesUntilGameIsStopped)
{
    runIterations(2);
    EXPECT_THAT(game.updateCount, Eq(2));
}

TEST_F(GameLoopTest, CallsInitialiseOnce)
{
    runIterations(3);
    int initCount = std::count(game.calls.begin(), game.calls.end(), "init");
    EXPECT_THAT(initCount, Eq(1));
}

TEST_F(GameLoopTest, CallsGameFunctionsInExpectedOrder)
{
    runIterations(1);
    EXPECT_THAT(game.calls, ElementsAre("init", "update", "draw"));
}
