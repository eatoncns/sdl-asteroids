#include <gmock/gmock.h>
#include <Asteroid.hpp>
#include <Rectangle.hpp>
#include <MoveableObjectTest.hpp>
#include <TestRandomGenerator.hpp>
#include <boost/math/special_functions/round.hpp>

using namespace pjm;
using boost::shared_ptr;
using boost::math::iround;
using ::testing::Eq;
using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Return;


struct AsteroidSpy : public Asteroid
{
    AsteroidSpy(shared_ptr<ScreenWrapper> iScreenWrapper)
        : Asteroid(iScreenWrapper)
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
            : _asteroid(_wrapper),
              _velocityComponent(sin(45*M_PI/180.0)*Asteroid::VELOCITY)
        {
            ON_CALL(_random, uniformInRange(_,_))
                .WillByDefault(Return(0.375));
            _asteroid.initialise(_initialLocation, _imageLoader, _random);
        }
        
        NiceMock<TestRandomGenerator> _random;
        AsteroidSpy _asteroid;
        float _velocityComponent;
};


TEST_F(AsteroidTest, InitReturnsFalseWhenImageLoadFails)
{
    _imageLoader.loadSuccess = false;
    EXPECT_FALSE(_asteroid.initialise(_initialLocation, _imageLoader, _random));
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
    EXPECT_THAT(_testRenderable->renderCalls, ElementsAre(std::make_pair(_initialLocation, 0.0)));
}

TEST_F(AsteroidTest, HasBoundingBoxBasedOnScaledImage)
{
    int testLength = 53;
    _testRenderable->w = testLength;
    _testRenderable->h = testLength;
    Rectangle boundingBox = _asteroid.getBoundingBox();
    float ratioLength = testLength*MovingObject::BOUNDING_BOX_RATIO;
    EXPECT_THAT(boundingBox.x, Eq(_initialLocation.x + ratioLength));
    EXPECT_THAT(boundingBox.y, Eq(_initialLocation.y + ratioLength));
    EXPECT_THAT(boundingBox.w, Eq(iround(testLength - 2*ratioLength)));
    EXPECT_THAT(boundingBox.h, Eq(iround(testLength - 2*ratioLength)));
}

TEST_F(AsteroidTest, SwapsVelocityWithOtherAsteroidOnCollision)
{
    AsteroidSpy otherAsteroid(_wrapper);
    Vector otherVelocity(1, 1);
    otherAsteroid.setVelocity(otherVelocity);
    _asteroid.collideWith(&otherAsteroid);
    EXPECT_THAT(_asteroid.getVelocity(),
                Eq(otherVelocity));
    EXPECT_THAT(otherAsteroid.getVelocity(), 
                Eq(Vector(_velocityComponent, _velocityComponent)));
}
