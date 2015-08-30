#include <Ship.hpp>
#include <Renderable.hpp>

namespace pjm
{
    Ship::Ship(Coordinate iInitialLocation, Renderable& iImage)
      : _location(iInitialLocation),
        _image(iImage)
    {}
    
    
    void Ship::render()
    {
        static int widthOffset = _image.width() / 2;
        static int heightOffset = _image.height() / 2;
        int renderX = _location.x - widthOffset;
        int renderY = _location.y - heightOffset;
        Coordinate renderLocation(renderX, renderY);
        _image.render(renderLocation);
    }
}
