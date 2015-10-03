#include <gmock/gmock.h>
#include <AsteroidCreator.hpp>
#include <ScreenWrapper.hpp>
#include <TestRandomGenerator.hpp>
#include <TestAsteroid.hpp>
#include <TestLocationGenerator.hpp>
#include <boost/foreach.hpp>

using namespace pjm;
using boost::shared_ptr;
using std::list;
using ::testing::Eq;
using ::testing::Each;
using ::testing::NiceMock;

struct TestableAsteroidCreator : public AsteroidCreator
{
    TestableAsteroidCreator()
        : testAsteroid(new TestAsteroid())
    {}

    shared_ptr<Asteroid> makeAsteroid(shared_ptr<ScreenWrapper>,
                                      RandomGenerator&)
    {
        return testAsteroid;
    }

    shared_ptr<TestAsteroid> testAsteroid;
};

class AsteroidCreatorTest : public ::testing::Test
{
    protected:
        list<shared_ptr<Asteroid> > create()
        {
            return asteroidCreator.create(screenWrapper,
                                          imageLoader,
                                          locationGenerator,
                                          random);
        }

        shared_ptr<ScreenWrapper> screenWrapper;
        TestImageLoader imageLoader;
        TestLocationGenerator locationGenerator;
        NiceMock<TestRandomGenerator> random;
        TestableAsteroidCreator asteroidCreator;
};

TEST_F(AsteroidCreatorTest, ReturnsValidAsteroidPointersWhenInitialiseSucceeds)
{
    list<shared_ptr<Asteroid> > asteroids = create();
    BOOST_FOREACH(shared_ptr<Asteroid> asteroid, asteroids)
    {
        EXPECT_TRUE(asteroid); 
    }
}

TEST_F(AsteroidCreatorTest, ReturnsEmptyVectorWhenAsteroidInitialiseFails)
{
    asteroidCreator.testAsteroid->initialiseSuccess = false;
    list<shared_ptr<Asteroid> > asteroids = create();
    EXPECT_THAT(asteroids.empty(), Eq(true));
}

TEST_F(AsteroidCreatorTest, CreatesFixedNumberOfAsteroids)
{
    list<shared_ptr<Asteroid> > asteroids = create();
    EXPECT_THAT(asteroids.size(), Eq(AsteroidCreator::NUM_ASTEROIDS));
}

TEST_F(AsteroidCreatorTest, InitialisesFixedNumberOfAsteroids)
{
    create();
    EXPECT_THAT(asteroidCreator.testAsteroid->initialiseCalls.size(),
                Eq(AsteroidCreator::NUM_ASTEROIDS));
}

TEST_F(AsteroidCreatorTest, IntialisesAsteroidsAtRandomLocation)
{
    create();
    EXPECT_THAT(asteroidCreator.testAsteroid->initialiseCalls,
                Each(Vector(TestLocationGenerator::x, TestLocationGenerator::y)));
}
