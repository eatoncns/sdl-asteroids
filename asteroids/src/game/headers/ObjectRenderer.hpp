#ifndef _PJM_OBJECTRENDERER_HPP_
#define _PJM_OBJECTRENDERER_HPP_

#include <string>
#include <boost/shared_ptr.hpp>

namespace pjm
{
    struct ImageLoader;
    struct Renderable;
    class Rectangle;
    class Vector;

    class ObjectRenderer
    {
        public:
            bool initialise(ImageLoader& iImageLoader,
                            const std::string& iFilePath);

            void renderAt(const Vector& iLocation,
                          const double iAngle);

            Rectangle getBoundingBox(const Vector& iLocation);

            const static float BOUNDING_BOX_RATIO;

        private:
            boost::shared_ptr<Renderable> _image;
    };
}

#endif /* end of include guard: _PJM_OBJECTRENDERER_HPP_ */
