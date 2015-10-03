#include <gmock/gmock.h>
#include <Asteroid.hpp>
#include <Rectangle.hpp>
#include <MoveableObjectTest.hpp>
#include <TestRandomGenerator.hpp>

using namespace pjm;
using boost::shared_ptr;
using ::testing::Eq;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Return;


struct AsteroidSpy : public Asteroid
{
    AsteroidSpy(shared_ptr<ScreenWrapper> iScreenWrapper,
                RandomGenerator& iRandomGenerator)
        : Asteroid(iScreenWrapper, iRandomGenerator)
    {}

    Vector getLocation()
    {
        return _location;
    }

    Vector getVelocity()
    {
        return _velocity;
    }

    void setVelocity(const Vector& iVelocity)
    {
        _velocity = iVelocity;
    }
};


class AsteroidTest : public MoveableObjectTest
{
    protected:
        AsteroidTest()
            : _asteroid(_wrapper, _random),
              _velocityComponent(sin(45*M_PI/180.0)*Asteroid::VELOCITY)
        {
            ON_CALL(_random, uniformInRange(_,_))
                .WillByDefault(Return(0.375));
            _asteroid.initialise(_initialLocation, _imageLoader);
        }
        
        NiceMock<TestRandomGenerator> _random;
        AsteroidSpy _asteroid;
        float _velocityComponent;
};


TEST_F(AsteroidTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_asteroid.initialise(_initialLocation, _imageLoader));
}

TEST_F(AsteroidTest, InitialisesWithFixedVelocityInRandomDirection)
{ 
    EXPECT_THAT(_asteroid.getVelocity(), Eq(Vector(_velocityComponent, _velocityComponent)));
}

TEST_F(AsteroidTest, MovesWithConstantVelocity)
{
    _asteroid.update(5);
    float distanceComponent = _velocityComponent*5;
    EXPECT_THAT(_asteroid.getLocation(), Eq(Vector(_initialLocation.x + distanceComponent,
                                                   _initialLocation.y + distanceComponent)));
}

TEST_F(AsteroidTest, CallsScreenWrapperOnUpdate)
{
    float distanceComponent = _velocityComponent*5;
    Vector location(_initialLocation.x + distanceComponent, _initialLocation.y + distanceComponent);
    Vector velocity(_velocityComponent, _velocityComponent);
    EXPECT_CALL(*_wrapper, wrap(location, velocity, 5));
    _asteroid.update(5);
}

TEST_F(AsteroidTest, RendersImageAtCurrentLocation)
{
    _asteroid.render();
    EXPECT_THAT(_testRenderable.renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}

TEST_F(AsteroidTest, HasBoundingBoxBasedOnImage)
{
    _testRenderable.w = 5;
    _testRenderable.h = 6;
    Rectangle boundingBox = _asteroid.getBoundingBox();
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y));
    EXPECT_THAT(boundingBox.w, Eq(5));
    EXPECT_THAT(boundingBox.h, Eq(6));
}

TEST_F(AsteroidTest, SwapsVelocityWithOtherAsteroidOnCollision)
{
    AsteroidSpy otherAsteroid(_wrapper, _random);
    Vector otherVelocity(1, 1);
    otherAsteroid.setVelocity(otherVelocity);
    _asteroid.collideWith(&otherAsteroid);
    EXPECT_THAT(_asteroid.getVelocity(),
                Eq(otherVelocity));
    EXPECT_THAT(otherAsteroid.getVelocity(), 
                Eq(Vector(_velocityComponent, _velocityComponent)));
}
