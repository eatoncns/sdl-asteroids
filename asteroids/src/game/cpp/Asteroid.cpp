#include <Asteroid.hpp>
#include <RandomGenerator.hpp>
#include <ScreenWrapper.hpp>
#include <math.h>

namespace pjm
{ 
    Asteroid::Asteroid(ImageLoader& iImageLoader, 
                       ScreenWrapper& iScreenWrapper, 
                       RandomGenerator& iRandomGenerator)
        : MovingObject(iImageLoader, iScreenWrapper),
          _random(iRandomGenerator)
    {}
    
    
    bool Asteroid::initialise(const Vector& iInitialLocation)
    {
        float angle = _random.uniformInRange(0, 1) * 2 * M_PI;
        _velocity.x = sin(angle);
        _velocity.y = -cos(angle);
        _velocity *= VELOCITY;
        return MovingObject::initialise(iInitialLocation);
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

    
    std::string Asteroid::imageFilePath()
    {
        return "resources/Asteroid.gif";
    }


    Asteroid* Asteroid::create(ImageLoader& iImageLoader,
                               ScreenWrapper& iScreenWrapper,
                               RandomGenerator& iRandomGenerator)
    {
        return new Asteroid(iImageLoader, iScreenWrapper, iRandomGenerator);
    }

    
    float Asteroid::VELOCITY = 0.08;
}
