#include <Bullet.hpp>
#include <ScreenWrapper.hpp>
#include <boost/make_shared.hpp>

using boost::make_shared;

namespace pjm
{
    Bullet::Bullet(const Vector& iBounds)
        : MovingObject(make_shared<ScreenWrapper>(Vector(0, 0)))
    {
    
    }

    
    bool Bullet::initialise(const Vector& iInitialLocation,
                            const Vector& iShooterVelocity,
                            ImageLoader& iImageLoader)
    {
        return true;
    }


    std::string Bullet::imageFilePath()
    {
        return "resources/Bullet.gif";
    }
    
}
