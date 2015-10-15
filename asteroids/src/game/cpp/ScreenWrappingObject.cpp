#include <ScreenWrappingObject.hpp>
#include <ScreenWrapper.hpp>

namespace pjm
{
    ScreenWrappingObject::ScreenWrappingObject(boost::shared_ptr<ScreenWrapper> iScreenWrapper)
        : _screenWrapper(iScreenWrapper)
    {}

    void ScreenWrappingObject::handleScreenWrap(unsigned int iTimeElapsed)
    {
        _screenWrapper->wrap(_location, _velocity, iTimeElapsed);
    }
}
