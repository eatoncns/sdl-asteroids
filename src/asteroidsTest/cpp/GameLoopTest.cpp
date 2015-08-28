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
        : passInitialisation(true),
          iterations(0)
    {}

    bool isRunning()
    {
        return (iterations-- > 0);
    }

    bool initialise()
    {
        calls.push_back("init");
        return passInitialisation;
    }

    void update()
    {
        calls.push_back("update");
    }

    void draw()
    {
        calls.push_back("draw");
    }

    bool passInitialisation;
    unsigned int iterations;
    std::list<std::string> calls;
};


class GameLoopTest : public ::testing::Test
{
    protected:
        GameLoopTest()
            : gameLoop(game)
        {}

        bool runIterations(const unsigned int iIterations)
        {
            game.iterations = iIterations;
            return gameLoop.run();
        }

        int callCount(const std::string& iFunction)
        {
            return std::count(game.calls.begin(), game.calls.end(), iFunction);
        }

        TestGame game;
        GameLoop gameLoop;
};

TEST_F(GameLoopTest, DoesNoUpdatesWhenGameIsStopped)
{
    runIterations(0);
    EXPECT_THAT(callCount("update"), Eq(0));
}

TEST_F(GameLoopTest, UpdatesUntilGameIsStopped)
{
    runIterations(2);
    EXPECT_THAT(callCount("update"), Eq(2));
}

TEST_F(GameLoopTest, DrawsUntilGameIsStopped)
{
    runIterations(2);
    EXPECT_THAT(callCount("draw"), Eq(2));
}

TEST_F(GameLoopTest, CallsInitialiseOnce)
{
    runIterations(3);
    EXPECT_THAT(callCount("init"), Eq(1));
}

TEST_F(GameLoopTest, CallsGameFunctionsInExpectedOrder)
{
    runIterations(1);
    EXPECT_THAT(game.calls, ElementsAre("init", "update", "draw"));
}

TEST_F(GameLoopTest, DoesNoUpdatesWhenInitialisationFails)
{
    game.passInitialisation = false;
    runIterations(1);
    EXPECT_THAT(callCount("update"), Eq(0));
}

TEST_F(GameLoopTest, IndicatesIntialisationFailure)
{
    game.passInitialisation = false;
    EXPECT_FALSE(runIterations(1)); 
}
