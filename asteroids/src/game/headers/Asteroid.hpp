#ifndef _PJM_ASTEROID_HPP_
#define _PJM_ASTEROID_HPP_

#include <MovingObject.hpp>

namespace pjm
{
    class Asteroid : public MovingObject
    {
        public:
            Asteroid(ImageLoader& iImageLoader, ScreenWrapper& iScreenWrapper)
                : MovingObject(iImageLoader, iScreenWrapper)
            {}
            
            virtual ~Asteroid() {}

        protected:
            virtual std::string imageFilePath();

    };
}

#endif
