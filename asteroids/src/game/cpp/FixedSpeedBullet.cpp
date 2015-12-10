#include <FixedSpeedBullet.hpp>
#include <ScreenWrapper.hpp>
#include <boost/make_shared.hpp>
#include <math.h>

using boost::make_shared;

namespace pjm
{
    FixedSpeedBullet::FixedSpeedBullet(const Vector& iBounds)
        : _bounds(iBounds)
    {}


    bool FixedSpeedBullet::initialise(const Vector& iInitialLocation,
                            const double iAngle,
                            ImageLoader& iImageLoader)
    {
        double angleRadians = iAngle*M_PI/180.0;
        double sinAngle = sin(angleRadians);
        double cosAngle = -cos(angleRadians);
        _velocity = Vector(sinAngle, cosAngle);
        _velocity *= VELOCITY;
        return MovingObject::initialise(iInitialLocation, iImageLoader);
    }


    void FixedSpeedBullet::update(unsigned int iTimeElapsed)
    {
        MovingObject::updateLocation(iTimeElapsed);
        _expired = isOutsideOfScreen();
    }


    bool FixedSpeedBullet::isOutsideOfScreen()
    {
        return (_location.x < 0 ||
                _location.y < 0 ||
                _location.x > _bounds.x ||
                _location.y > _bounds.y);
    }


    void FixedSpeedBullet::collideWith(Asteroid* iAsteroid)
    {
        _expired = true;
    }


    std::string FixedSpeedBullet::imageFilePath()
    {
        return "resources/Bullet.gif";
    }


    const float FixedSpeedBullet::VELOCITY(0.5);
}
