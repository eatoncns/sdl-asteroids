#include <MovingObject.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <ScreenWrapper.hpp>
#include <Rectangle.hpp>
#include <boost/math/special_functions/round.hpp>

using boost::shared_ptr;
using boost::math::iround;

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


    Rectangle MovingObject::getBoundingBox()
    {
        float ratioWidth = BOUNDING_BOX_RATIO*_image->width();
        float ratioHeight = BOUNDING_BOX_RATIO*_image->height();
        return Rectangle(_location.x + ratioWidth,
                         _location.y + ratioHeight,
                         iround(_image->width() - 2*ratioWidth),
                         iround(_image->height() - 2*ratioHeight));
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

    const float MovingObject::BOUNDING_BOX_RATIO = 0.2;
}
