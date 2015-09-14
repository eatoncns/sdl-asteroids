#ifndef _PJM_MOVINGOBJECT_HPP_
#define _PJM_MOVINGOBJECT_HPP_

#include <Vector.hpp>

namespace pjm
{
    struct Renderable;
    struct ImageLoader;
    struct ScreenWrapper;
    
    class MovingObject
    {
        public:
            virtual bool initialise(const Vector& iInitialLocation);
            virtual void render();

        protected:
            MovingObject(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper);

            virtual std::string imageFilePath() = 0;

            virtual void handleScreenWrap(unsigned int iTimeElapsed);
            
            virtual ~MovingObject() {}

            Vector _location;
            Vector _velocity;
            double _angle;
            ScreenWrapper& _screenWrapper;
            ImageLoader& _imageLoader;
            Renderable* _image;


    };
}

#endif
