#include <Asteroid.hpp>
#include <RandomGenerator.hpp>
#include <ScreenWrapper.hpp>
#include <math.h>

using boost::shared_ptr;

namespace pjm
{
    Asteroid::Asteroid(shared_ptr<ScreenWrapper> iScreenWrapper)
        : ScreenWrappingObject(iScreenWrapper)
    {}


    bool Asteroid::initialise(const Vector& iInitialLocation,
                              ImageLoader& iImageLoader,
                              RandomGenerator& iRandomGenerator)
    {
        float angle = iRandomGenerator.uniformInRange(0, 1) * 2 * M_PI;
        _velocity.x = sin(angle);
        _velocity.y = -cos(angle);
        _velocity *= VELOCITY;
        return MovingObject::initialise(iInitialLocation, iImageLoader);
    }


    void Asteroid::update(unsigned int iTimeElapsed)
    {
        updateLocation(iTimeElapsed);
        handleScreenWrap(iTimeElapsed);
    }


    void Asteroid::collideWith(Asteroid* iOther)
    {
        Vector tmp = _velocity;
        _velocity = iOther->_velocity;
        iOther->_velocity = tmp;
    }


    void Asteroid::collideWith(FixedSpeedBullet* iBullet)
    {
        _expired = true;
    }


    std::string Asteroid::imageFilePath()
    {
        return "resources/Asteroid.gif";
    }


    float Asteroid::VELOCITY = 0.08;
}
