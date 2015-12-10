#include <FixedSpeedAsteroid.hpp>
#include <RandomGenerator.hpp>
#include <Rectangle.hpp>
#include <ScreenWrapper.hpp>
#include <Vector.hpp>
#include <math.h>

using boost::shared_ptr;

namespace pjm
{
    FixedSpeedAsteroid::FixedSpeedAsteroid(shared_ptr<ScreenWrapper> iScreenWrapper)
        : _screenWrapper(iScreenWrapper),
          _expired(false)
    {}


    bool FixedSpeedAsteroid::initialise(const Vector& iInitialLocation,
                              ImageLoader& iImageLoader,
                              RandomGenerator& iRandomGenerator)
    {
        _physicsData.location = iInitialLocation;
        float angle = iRandomGenerator.uniformInRange(0, 1) * 2 * M_PI;
        _physicsData.velocity.x = sin(angle);
        _physicsData.velocity.y = -cos(angle);
        _physicsData.velocity *= VELOCITY;
        return _renderer.initialise(iImageLoader, imageFilePath);
    }


    void FixedSpeedAsteroid::update(unsigned int iTimeElapsed)
    {
        _physicsData.updateLocation(iTimeElapsed);
        _screenWrapper->wrap(_physicsData.location,
                             _physicsData.velocity,
                             iTimeElapsed);
    }


    void FixedSpeedAsteroid::render()
    {
        static const double fixedAngle = 0.0;
        _renderer.renderAt(_physicsData.location, fixedAngle);
    }


    Rectangle FixedSpeedAsteroid::getBoundingBox()
    {
        return _renderer.getBoundingBox(_physicsData.location);
    }


    void FixedSpeedAsteroid::collideWith(Asteroid* iOther)
    {
        Vector tmp = getNormalisedDirection();
        setNormalisedDirection(iOther->getNormalisedDirection());
        iOther->setNormalisedDirection(tmp);
    }


    void FixedSpeedAsteroid::collideWith(Bullet* iBullet)
    {
        _expired = true;
    }


    bool FixedSpeedAsteroid::isExpired()
    {
        return _expired;
    }


    Vector FixedSpeedAsteroid::getNormalisedDirection()
    {
        Vector velocity = _physicsData.velocity;
        float velocityMagnitude = sqrt(velocity.squareSum());
        velocity *= (1/velocityMagnitude);
        return velocity;
    }


    void FixedSpeedAsteroid::setNormalisedDirection(const Vector& iNormalisedDirection)
    {
        _physicsData.velocity = iNormalisedDirection;
        _physicsData.velocity *= VELOCITY;
    }


    const std::string FixedSpeedAsteroid::imageFilePath = "resources/Asteroid.gif";


    const float FixedSpeedAsteroid::VELOCITY = 0.08;
}
