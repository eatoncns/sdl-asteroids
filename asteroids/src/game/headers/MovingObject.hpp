#ifndef _PJM_MOVINGOBJECT_HPP_
#define _PJM_MOVINGOBJECT_HPP_

#include <Vector.hpp>
#include <boost/shared_ptr.hpp>

namespace pjm
{
    struct Renderable;
    struct ImageLoader;
    struct ScreenWrapper;
    struct Rectangle;

    class MovingObject
    {
        public:
            virtual bool initialise(const Vector& iInitialLocation,
                                    ImageLoader& iImageLoader);
            virtual Rectangle getBoundingBox();
            virtual void render();

            const static float BOUNDING_BOX_RATIO;

        protected:
            MovingObject();

            virtual std::string imageFilePath() = 0;

            virtual void updateLocation(unsigned int iTimeElapsed);

            virtual ~MovingObject() {}

            Vector _location;
            Vector _velocity;
            double _angle;
            boost::shared_ptr<Renderable> _image;
    };
}

#endif
