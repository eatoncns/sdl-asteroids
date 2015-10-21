#include <BulletLoader.hpp>

using boost::shared_ptr;

namespace pjm
{
    BulletLoader::BulletLoader(ImageLoader& iImageLoader)
        : _imageLoader(iImageLoader)
    {}

    shared_ptr<Bullet> BulletLoader::loadBullet()
    {
        return shared_ptr<Bullet>();
    }
}
