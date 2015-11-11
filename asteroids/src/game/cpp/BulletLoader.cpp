#include <BulletLoader.hpp>
#include <Bullet.hpp>
#include <Timer.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

namespace pjm
{
    BulletLoader::BulletLoader(const Vector& iBounds,
                               ImageLoader& iImageLoader,
                               Timer& iTimer)
        : _bounds(iBounds),
          _imageLoader(iImageLoader),
          _timer(iTimer),
          _previousShotTime(_timer.getTime())
    {}


    shared_ptr<Bullet> BulletLoader::loadBullet(const Vector& iInitialLocation,
                                                const Vector& iInitialDirection)
    {
        unsigned int time = _timer.getTime();
        if (time - _previousShotTime >= RELOAD_TIME)
        {
            _previousShotTime = time;
            shared_ptr<Bullet> bullet = makeBullet();
            if (bullet->initialise(iInitialLocation, iInitialDirection, _imageLoader))
            {
                return bullet;
            }
        }
        return shared_ptr<Bullet>();
    }


    shared_ptr<Bullet> BulletLoader::makeBullet()
    {
        return shared_ptr<Bullet>(new Bullet(_bounds));
    }


    const unsigned int BulletLoader::RELOAD_TIME = 10;
}
