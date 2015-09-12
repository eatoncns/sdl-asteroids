#ifndef _PJM_SCREENWRAPPER_HPP_
#define _PJM_SCREENWRAPPER_HPP_

#include <Vector.hpp>

namespace pjm
{
    class ScreenWrapper
    {
        public:
            explicit ScreenWrapper(const Vector& iBounds);

            void wrap(Vector& ioLocation, 
                      const Vector& iVelocity, 
                      unsigned int iTimeElapsed);

        private:
            bool isOutsideOfScreen(const Vector& iLocation);

            bool wrapLeftOrRight(Vector& ioLocation, 
                      const Vector& iVelocity, 
                      unsigned int iTimeElapsed);
            
            bool wrapTopOrBottom(Vector& ioLocation, 
                      const Vector& iVelocity, 
                      unsigned int iTimeElapsed);
            
            Vector _bounds;
    };
}

#endif
