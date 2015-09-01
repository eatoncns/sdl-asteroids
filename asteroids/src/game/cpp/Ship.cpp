#include <Ship.hpp>
#include <Renderable.hpp>

namespace pjm
{
    Ship::Ship(const Vector& iInitialLocation, Renderable& iImage)
      : _location(iInitialLocation),
        _previousLocation(iInitialLocation),
        _acceleration(0, 0),
        _image(iImage)
    {}
    
    
    void Ship::render()
    {
        static int widthOffset = _image.width() / 2;
        static int heightOffset = _image.height() / 2;
        float renderX = _location.x - widthOffset;
        float renderY = _location.y - heightOffset;
        Vector renderLocation(renderX, renderY);
        _image.render(renderLocation);
    }


    void Ship::update(const Action iAction, unsigned int iTimeElapsed)
    {
         if(iAction == ACCELERATE)
         {
             _acceleration.y += ACC_FACTOR;
         }
         else
         {
             if (_acceleration.y > ACC_FACTOR)
             {
                _acceleration.y -= ACC_FACTOR;
             }
             else
             {
                _acceleration.y = 0;
             }
         }
         Vector currentLocation(_location);
         // Minus accelration as we consider origin to be at
         // top left of screen
         _location = currentLocation*2 - _previousLocation - 
                     _acceleration*iTimeElapsed*iTimeElapsed;
         _previousLocation = currentLocation;
    }
}
