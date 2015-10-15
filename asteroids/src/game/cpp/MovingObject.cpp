#include <MovingObject.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <ScreenWrapper.hpp>
#include <Rectangle.hpp>

using boost::shared_ptr;

namespace pjm
{
    MovingObject::MovingObject()
        : _location(0, 0),
          _velocity(0, 0),
          _angle(0.0)
    {}


    bool MovingObject::initialise(const Vector& iInitialLocation,
                                  ImageLoader& iImageLoader)
    {
        _location = iInitialLocation;
        _image = iImageLoader.loadFromFile(imageFilePath());
        return _image;
    }


    void MovingObject::updateLocation(unsigned int iTimeElapsed)
    {
        _location += _velocity*iTimeElapsed;
    }


    void MovingObject::render()
    {
        int widthOffset = _image->width() / 2;
        int heightOffset = _image->height() / 2;
        float renderX = _location.x - widthOffset;
        float renderY = _location.y - heightOffset;
        Vector renderLocation(renderX, renderY);
        _image->render(renderLocation, _angle);
    }

}
