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


    shared_ptr<Bullet> BulletLoader::loadBullet()
    {
        unsigned int time = _timer.getTime();
        if (time - _previousShotTime >= RELOAD_TIME)
        {
            return make_shared<Bullet>(_bounds);
        }
        return shared_ptr<Bullet>();
    }


    const unsigned int BulletLoader::RELOAD_TIME = 10;
}
