#include <gmock/gmock.h>
#include <LifeCounter.hpp>
#include <TestImageLoader.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using boost::shared_ptr;
using ::testing::Eq;

class LifeCounterTest : public ::testing::Test
{
    protected:
        LifeCounterTest()
            : _renderable(new TestRenderable()),
              _initialLocation(5, 5),
              _initialLives(2),
              _lifeCounter(_initialLocation, _initialLives)
        {
            _imageLoader.renderable = _renderable;
            _lifeCounter.initialise(_imageLoader);
        }

        TestImageLoader _imageLoader;
        shared_ptr<TestRenderable> _renderable;
        Vector _initialLocation;
        int _initialLives;
        LifeCounter _lifeCounter;
};


TEST_F(LifeCounterTest, intialiseReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_THAT(_lifeCounter.initialise(_imageLoader), Eq(false));
}

TEST_F(LifeCounterTest, initialiseReturnsTrueWhenImageLoadSucceeds)
{
    EXPECT_THAT(_lifeCounter.initialise(_imageLoader), Eq(true));
}
