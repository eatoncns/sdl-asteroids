#include <MovingObject.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <ScreenWrapper.hpp>
#include <Rectangle.hpp>

using boost::shared_ptr;

namespace pjm
{
    MovingObject::MovingObject(shared_ptr<ScreenWrapper> iScreenWrapper)
        : _location(0, 0),
          _velocity(0, 0),
          _angle(0.0),
          _screenWrapper(iScreenWrapper),
          _image(NULL)
    {}

    
    bool MovingObject::initialise(const Vector& iInitialLocation,
                                  ImageLoader& iImageLoader)
    {
        _location = iInitialLocation;
        _image = iImageLoader.loadFromFile(imageFilePath());
        return (_image != NULL);
    }
 

    void MovingObject::updateLocation(unsigned int iTimeElapsed)
    {
        _location += _velocity*iTimeElapsed;
    }

    
    void MovingObject::handleScreenWrap(unsigned int iTimeElapsed)
    {
        _screenWrapper->wrap(_location, _velocity, iTimeElapsed);
    }


    Rectangle MovingObject::getBoundingBox()
    {
        return Rectangle(_location.x,
                         _location.y,
                         _image->width(),
                         _image->height());    
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
