#include <TimeLimitedBulletLoader.hpp>
#include <FixedSpeedBullet.hpp>
#include <Timer.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

namespace pjm
{
    TimeLimitedBulletLoader::TimeLimitedBulletLoader(const Vector& iBounds,
                               ImageLoader& iImageLoader,
                               Timer& iTimer)
        : _bounds(iBounds),
          _imageLoader(iImageLoader),
          _timer(iTimer),
          _previousShotTime(_timer.getTime())
    {}


    shared_ptr<Bullet> TimeLimitedBulletLoader::loadBullet(const Vector& iInitialLocation,
                                                const double iAngle)
    {
        unsigned int time = _timer.getTime();
        if (time - _previousShotTime >= RELOAD_TIME)
        {
            _previousShotTime = time;
            shared_ptr<Bullet> bullet = makeBullet();
            if (bullet->initialise(iInitialLocation, iAngle, _imageLoader))
            {
                return bullet;
            }
        }
        return shared_ptr<Bullet>();
    }


    shared_ptr<Bullet> TimeLimitedBulletLoader::makeBullet()
    {
        return shared_ptr<FixedSpeedBullet>(new FixedSpeedBullet(_bounds));
    }


    const unsigned int TimeLimitedBulletLoader::RELOAD_TIME = 1000;
}
