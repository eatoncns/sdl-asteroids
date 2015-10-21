#ifndef _PJM_BULLETLOADER_HPP_
#define _PJM_BULLETLOADER_HPP_

#include <boost/shared_ptr.hpp>

namespace pjm
{
    struct ImageLoader;
    struct Timer;
    class Bullet;

    class BulletLoader
    {
        public:
            BulletLoader(ImageLoader& iImageLoader, Timer& iTimer);

            boost::shared_ptr<Bullet> loadBullet();

        private:
            ImageLoader& _imageLoader;
            Timer& _timer;
    };
}

#endif /* end of include guard: _PJM_BULLETLOADER_HPP_ */
