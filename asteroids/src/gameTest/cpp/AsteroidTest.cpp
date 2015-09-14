#include <gmock/gmock.h>
#include <Asteroid.hpp>
#include <MoveableObjectTest.hpp>
#include <RandomGenerator.hpp>
#include <boost/assign/list_of.hpp>
#include <queue>

using namespace pjm;
using namespace boost::assign;
using ::testing::Eq;
using ::testing::ElementsAre;

struct TestRandomGenerator : RandomGenerator
{
    float uniformAboutZero(float iRange)
    {
        float result = sequence.front();
        sequence.pop();
        return result;
    }

    std::queue<float> sequence;
};


struct AsteroidSpy : public Asteroid
{
    AsteroidSpy(ImageLoader& iImageLoader,
                ScreenWrapper& iScreenWrapper,
                RandomGenerator& iRandomGenerator)
        : Asteroid(iImageLoader, iScreenWrapper, iRandomGenerator)
    {}

    Vector getVelocity()
    {
        return _velocity;
    }
};


class AsteroidTest : public MoveableObjectTest
{
    protected:
        AsteroidTest()
            : _asteroid(_imageLoader, _wrapper, _random)
        {
            _random.sequence = list_of(Asteroid::VELOCITY)(Asteroid::VELOCITY).to_adapter();
            _asteroid.initialise(_initialLocation);
        }
        
        TestRandomGenerator _random;
        AsteroidSpy _asteroid;
};


TEST_F(AsteroidTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_asteroid.initialise(_initialLocation));
}

TEST_F(AsteroidTest, RendersImageAtCurrentLocation)
{
    _asteroid.render();
    EXPECT_THAT(_testRenderable.renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}

TEST_F(AsteroidTest, HasFixedVelocityInRandomDirection)
{ 
    float velocityComponent = sin(45*M_PI/180.0)*Asteroid::VELOCITY;
    EXPECT_THAT(_asteroid.getVelocity(), Eq(Vector(velocityComponent, velocityComponent)));
}
