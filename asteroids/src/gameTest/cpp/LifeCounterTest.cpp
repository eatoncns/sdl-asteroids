#include <gmock/gmock.h>
#include <LifeCounter.hpp>
#include <TestImageLoader.hpp>
#include <TestRenderable.hpp>
#include <utility>

using namespace pjm;
using namespace std;
using boost::shared_ptr;
using ::testing::Eq;
using ::testing::ElementsAre;

class LifeCounterTest : public ::testing::Test
{
    protected:
        LifeCounterTest()
            : _renderable(new TestRenderable()),
              _initialLocation(5, 5),
              _initialLives(2),
              _lifeCounter(_initialLocation, _initialLives)
        {
            _renderable->w = 5;
            _renderable->h = 5;
            _imageLoader.renderable = _renderable;
            _lifeCounter.initialise(_imageLoader);
        }

        TestImageLoader _imageLoader;
        shared_ptr<TestRenderable> _renderable;
        Vector _initialLocation;
        int _initialLives;
        LifeCounter _lifeCounter;
};


TEST_F(LifeCounterTest, IntialiseReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_THAT(_lifeCounter.initialise(_imageLoader), Eq(false));
}

TEST_F(LifeCounterTest, InitialiseReturnsTrueWhenImageLoadSucceeds)
{
    EXPECT_THAT(_lifeCounter.initialise(_imageLoader), Eq(true));
}

TEST_F(LifeCounterTest, RendersRowOfLivesAtLocation)
{
    _lifeCounter.render();
    pair<Vector, double> firstLife = make_pair(_initialLocation, 0);
    pair<Vector, double> secondLife = make_pair(_initialLocation + Vector(_renderable->w, 0), 0);
    EXPECT_THAT(_renderable->renderCalls, ElementsAre(firstLife, secondLife));
}

TEST_F(LifeCounterTest, DecrementsLivesRendered)
{
    _lifeCounter.decrement();
    _lifeCounter.render();
    EXPECT_THAT(_renderable->renderCalls, ElementsAre(make_pair(_initialLocation, 0)));
}

TEST_F(LifeCounterTest, GameOverFalseWhenLivesLeft)
{
    EXPECT_THAT(_lifeCounter.gameOver(), Eq(false));
    _lifeCounter.decrement();
    EXPECT_THAT(_lifeCounter.gameOver(), Eq(false));
}

TEST_F(LifeCounterTest, GameOverTrueWhenNoLivesLeft)
{
    _lifeCounter.decrement();
    _lifeCounter.decrement();
    EXPECT_THAT(_lifeCounter.gameOver(), Eq(true)); 
}
