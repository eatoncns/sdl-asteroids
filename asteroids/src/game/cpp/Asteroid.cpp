#include <Asteroid.hpp>
#include <RandomGenerator.hpp>
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
        _velocity.x  = _random.uniformAboutZero(VELOCITY);
        _velocity.y  = _random.uniformAboutZero(VELOCITY);
        float velocitySquared = _velocity.squareSum();
        float magnitude = sqrt(velocitySquared);
        _velocity *= VELOCITY/magnitude;
        return MovingObject::initialise(iInitialLocation);
    }


    void Asteroid::update(unsigned int iTimeElapsed)
    {
        updateLocation(iTimeElapsed);
    }

    
    std::string Asteroid::imageFilePath()
    {
        return "resources/Asteroid.gif";
    }

    
    float Asteroid::VELOCITY = 0.08;
}
