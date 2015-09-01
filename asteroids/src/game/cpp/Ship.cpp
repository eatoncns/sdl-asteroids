#include <Ship.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>

namespace pjm
{
    Ship::Ship(ImageLoader& iImageLoader)
      : _location(0, 0),
        _previousLocation(0, 0),
        _acceleration(0, 0),
        _imageLoader(iImageLoader),
        _image(NULL)
    {}
    

    bool Ship::initialise(const Vector& iInitialLocation)
    {
        _location = iInitialLocation;
        _previousLocation = iInitialLocation;
        _image = _imageLoader.loadFromFile("resources/Ship.gif");
        return (_image != NULL);
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
    
    
    void Ship::render()
    {
        static int widthOffset = _image->width() / 2;
        static int heightOffset = _image->height() / 2;
        float renderX = _location.x - widthOffset;
        float renderY = _location.y - heightOffset;
        Vector renderLocation(renderX, renderY);
        _image->render(renderLocation);
    }

    
    Ship* Ship::create(ImageLoader& iImageLoader)
    {
        return new Ship(iImageLoader);
    }
}
