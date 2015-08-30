#include <Ship.hpp>
#include <Renderable.hpp>

namespace pjm
{
    Ship::Ship(const Vector& iInitialLocation, Renderable& iImage)
      : _location(iInitialLocation),
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
}
