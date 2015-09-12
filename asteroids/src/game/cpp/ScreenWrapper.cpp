#include <ScreenWrapper.hpp>

namespace pjm
{
    ScreenWrapper::ScreenWrapper(const Vector& iBounds)
        : _bounds(iBounds)
    {}


    void ScreenWrapper::wrap(Vector& ioLocation,
                             const Vector& iVelocity,
                             unsigned int iTimeElapsed)
    {
        if (isOutsideOfScreen(ioLocation))
        {
            wrapLeftOrRight(ioLocation, iVelocity, iTimeElapsed) || 
            wrapTopOrBottom(ioLocation, iVelocity, iTimeElapsed);
        }
    }
    
    
    bool ScreenWrapper::isOutsideOfScreen(const Vector& iLocation)
    {
        return (iLocation.x < 0 || iLocation.x > _bounds.x ||
                iLocation.y < 0 || iLocation.y > _bounds.y);
    }
    
    
    bool ScreenWrapper::wrapLeftOrRight(Vector& ioLocation, const Vector& iVelocity, unsigned int iTimeElapsed)
    {
        float inverseVelocityRatio = iVelocity.y/iVelocity.x;
        float intersectionX = iVelocity.x > 0 ? 0 : _bounds.x; 
        float intersectionY = (inverseVelocityRatio*intersectionX) - (inverseVelocityRatio*ioLocation.x) + ioLocation.y;
        if (intersectionY > 0 && intersectionY < _bounds.y)
        {
            ioLocation.x = intersectionX + iVelocity.x*iTimeElapsed;
            ioLocation.y = intersectionY + iVelocity.y*iTimeElapsed;
            return true;
        }
        return false;
    }


    bool ScreenWrapper::wrapTopOrBottom(Vector& ioLocation, const Vector& iVelocity, unsigned int iTimeElapsed)
    {
        float velocityRatio = iVelocity.x / iVelocity.y;
        float intersectionY = iVelocity.y > 0 ? 0 : _bounds.y;
        float intersectionX = (velocityRatio*intersectionY) - (velocityRatio*ioLocation.y) + ioLocation.x;
        if (intersectionX > 0 && intersectionX < _bounds.x)
        {
            ioLocation.x = intersectionX + iVelocity.x*iTimeElapsed;
            ioLocation.y = intersectionY + iVelocity.y*iTimeElapsed;
            return true;
        }
        return false;
    }
}
