#ifndef _PJM_SCREENWRAPPER_HPP_
#define _PJM_SCREENWRAPPER_HPP_

#include <Vector.hpp>

namespace pjm
{
    class ScreenWrapper
    {
        public:
            explicit ScreenWrapper(const Vector& iBounds);

            virtual void wrap(Vector& ioLocation, 
                              const Vector& iVelocity, 
                              unsigned int iTimeElapsed) const;

            virtual ~ScreenWrapper() {}

        private:
            bool isOutsideOfScreen(const Vector& iLocation) const;

            bool wrapLeftOrRight(Vector& ioLocation, 
                      const Vector& iVelocity, 
                      unsigned int iTimeElapsed) const;
            
            bool wrapTopOrBottom(Vector& ioLocation, 
                      const Vector& iVelocity, 
                      unsigned int iTimeElapsed) const;
            
            Vector _bounds;
    };
}

#endif
