#include <Bullet.hpp>
#include <ScreenWrapper.hpp>
#include <boost/make_shared.hpp>
#include <math.h>

using boost::make_shared;

namespace pjm
{
    Bullet::Bullet(const Vector& iBounds)
        : MovingObject(make_shared<ScreenWrapper>(Vector(0, 0)))
    {
    
    }

    
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
    }


    std::string Bullet::imageFilePath()
    {
        return "resources/Bullet.gif";
    } 
}
