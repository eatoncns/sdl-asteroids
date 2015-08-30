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
        _image.render(_location);
    }
}
