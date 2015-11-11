#include <Bullet.hpp>
#include <ScreenWrapper.hpp>
#include <boost/make_shared.hpp>
#include <math.h>

using boost::make_shared;

namespace pjm
{
    Bullet::Bullet(const Vector& iBounds)
        : _bounds(iBounds)
    {}


    bool Bullet::initialise(const Vector& iInitialLocation,
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


    void Bullet::update(unsigned int iTimeElapsed)
    {
        MovingObject::updateLocation(iTimeElapsed);
        _expired = isOutsideOfScreen();
    }


    bool Bullet::isOutsideOfScreen()
    {
        return (_location.x < 0 ||
                _location.y < 0 ||
                _location.x > _bounds.x ||
                _location.y > _bounds.y);
    }


    void Bullet::collideWith(Asteroid* iAsteroid)
    {
        _expired = true;
    }


    std::string Bullet::imageFilePath()
    {
        return "resources/Bullet.gif";
    }


    const float Bullet::VELOCITY(1.02);
}
