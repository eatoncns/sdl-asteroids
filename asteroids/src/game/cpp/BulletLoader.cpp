#include <BulletLoader.hpp>

using boost::shared_ptr;

namespace pjm
{
    BulletLoader::BulletLoader(ImageLoader& iImageLoader, Timer& iTimer)
        : _imageLoader(iImageLoader), _timer(iTimer)
    {}

    shared_ptr<Bullet> BulletLoader::loadBullet()
    {
        return shared_ptr<Bullet>();
    }
}
