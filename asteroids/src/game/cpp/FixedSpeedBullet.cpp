#include <FixedSpeedBullet.hpp>
#include <ImageLoader.hpp>
#include <Rectangle.hpp>
#include <boost/make_shared.hpp>
#include <math.h>

using boost::make_shared;

namespace pjm
{
    FixedSpeedBullet::FixedSpeedBullet(const Vector& iBounds)
        : _bounds(iBounds),
          _expired(false)
    {}


    bool FixedSpeedBullet::initialise(const Vector& iInitialLocation,
                            const double iAngle,
                            ImageLoader& iImageLoader)
    {
        _physicsData.location = iInitialLocation;
        double angleRadians = iAngle*M_PI/180.0;
        double sinAngle = sin(angleRadians);
        double cosAngle = -cos(angleRadians);
        _physicsData.velocity = Vector(sinAngle, cosAngle);
        _physicsData.velocity *= VELOCITY;
        return _renderer.initialise(iImageLoader, imageFilePath);
    }


    void FixedSpeedBullet::update(unsigned int iTimeElapsed)
    {
        _physicsData.updateLocation(iTimeElapsed);
        _expired = isOutsideOfScreen();
    }


    bool FixedSpeedBullet::isOutsideOfScreen()
    {
        const Vector& location = _physicsData.location;
        return (location.x < 0 ||
                location.y < 0 ||
                location.x > _bounds.x ||
                location.y > _bounds.y);
    }


    void FixedSpeedBullet::render()
    {
        static const double fixedAngle = 0.0;
        _renderer.renderAt(_physicsData.location, fixedAngle);
    }


    Rectangle FixedSpeedBullet::getBoundingBox()
    {
        return _renderer.getBoundingBox(_physicsData.location);
    }


    void FixedSpeedBullet::collideWith(Asteroid* iAsteroid)
    {
        _expired = true;
    }


    bool FixedSpeedBullet::isExpired()
    {
        return _expired;
    }


    const std::string FixedSpeedBullet::imageFilePath = "resources/Bullet.gif";


    const float FixedSpeedBullet::VELOCITY(0.5);
}
