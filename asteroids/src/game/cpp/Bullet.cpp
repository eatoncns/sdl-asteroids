#include <Bullet.hpp>
#include <ScreenWrapper.hpp>
#include <boost/make_shared.hpp>
#include <math.h>

using boost::make_shared;

namespace pjm
{
    Bullet::Bullet(const Vector& iBounds)
        : MovingObject(make_shared<ScreenWrapper>(Vector(0, 0))),
          _expired(false),
          _bounds(iBounds)
    {}

    
    bool Bullet::initialise(const Vector& iInitialLocation,
                            const Vector& iShooterVelocity,
                            ImageLoader& iImageLoader)
    {
        _velocity = iShooterVelocity;
        float velocityFactor = VELOCITY/sqrt(_velocity.squareSum());
        _velocity *= velocityFactor;
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


    bool Bullet::isExpired()
    {
        return _expired;
    }


    std::string Bullet::imageFilePath()
    {
        return "resources/Bullet.gif";
    } 
}
