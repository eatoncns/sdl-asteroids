#include <ObjectRenderer.hpp>
#include <ImageLoader.hpp>
#include <Rectangle.hpp>
#include <Vector.hpp>
#include <boost/math/special_functions/round.hpp>

using boost::math::iround;
using boost::shared_ptr;

namespace pjm
{
    bool ObjectRenderer::initialise(ImageLoader& iImageLoader,
                                    const std::string& iFilePath)
    {
        _image = iImageLoader.loadFromFile(iFilePath);
        return _image;
    }


    void ObjectRenderer::renderAt(const Vector& iLocation,
                                  const double iAngle)
    {
        _image->render(iLocation, iAngle);
    }


    Rectangle ObjectRenderer::getBoundingBox(const Vector& iLocation)
    {
        float ratioWidth = BOUNDING_BOX_RATIO*_image->width();
        float ratioHeight = BOUNDING_BOX_RATIO*_image->height();
        return Rectangle(iLocation.x + ratioWidth,
                         iLocation.y + ratioHeight,
                         iround(_image->width() - 2*ratioWidth),
                         iround(_image->height() - 2*ratioHeight));
    }


    const float ObjectRenderer::BOUNDING_BOX_RATIO = 0.2;
}
