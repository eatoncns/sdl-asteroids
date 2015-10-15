#ifndef _PJM_SCREENWRAPPINGOBJECT_HPP_
#define _PJM_SCREENWRAPPINGOBJECT_HPP_

#include <MovingObject.hpp>

namespace pjm
{
    class ScreenWrapper;

    class ScreenWrappingObject : public MovingObject
    {
        public:
            ScreenWrappingObject(boost::shared_ptr<ScreenWrapper> iScreenWrapper);

            void handleScreenWrap(unsigned int iTimeElapsed);

        protected:
            boost::shared_ptr<ScreenWrapper> _screenWrapper;
    };
}

#endif /* end of include guard: _PJM_SCREENWRAPPINGOBJECT_HPP_ */
