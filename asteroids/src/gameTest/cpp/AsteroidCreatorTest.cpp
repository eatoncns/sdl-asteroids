#include <gmock/gmock.h>
#include <AsteroidCreator.hpp>
#include <ScreenWrapper.hpp>
#include <TestRandomGenerator.hpp>

using namespace pjm;
using boost::shared_ptr;
using std::list;

class AsteroidCreatorTest : public ::testing::Test
{
    protected:
        shared_ptr<ScreenWrapper> screenWrapper;
        TestRandomGenerator random;
        AsteroidCreator asteroidCreator;
};

TEST_F(AsteroidCreatorTest, InterfaceCompiles)
{
    list<shared_ptr<Asteroid> > asteroids = asteroidCreator.create(screenWrapper, random);
}
