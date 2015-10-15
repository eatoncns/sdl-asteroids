#include <CollidableObject.hpp>
#include <Renderable.hpp>
#include <Rectangle.hpp>
#include <boost/math/special_functions/round.hpp>

using boost::math::iround;

namespace pjm
{
    Rectangle CollidableObject::getBoundingBox()
    {
        float ratioWidth = BOUNDING_BOX_RATIO*_image->width();
        float ratioHeight = BOUNDING_BOX_RATIO*_image->height();
        return Rectangle(_location.x + ratioWidth,
                         _location.y + ratioHeight,
                         iround(_image->width() - 2*ratioWidth),
                         iround(_image->height() - 2*ratioHeight));
    }


    const float CollidableObject::BOUNDING_BOX_RATIO = 0.2;
}
