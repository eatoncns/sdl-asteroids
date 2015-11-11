#ifndef _PJM_BULLETLOADER_HPP_
#define _PJM_BULLETLOADER_HPP_

#include <Vector.hpp>
#include <boost/shared_ptr.hpp>

namespace pjm
{
    struct ImageLoader;
    struct Timer;
    class Bullet;

    class BulletLoader
    {
        public:
            BulletLoader(const Vector& iBounds,
                         ImageLoader& iImageLoader,
                         Timer& iTimer);

            virtual boost::shared_ptr<Bullet> loadBullet(const Vector& iInitialLocation,
                                                         const Vector& iInitialDirection);

            const static unsigned int RELOAD_TIME;

        protected:
            virtual boost::shared_ptr<Bullet> makeBullet();

        private:
            Vector _bounds;
            ImageLoader& _imageLoader;
            Timer& _timer;
            unsigned int _previousShotTime;
    };
}

#endif /* end of include guard: _PJM_BULLETLOADER_HPP_ */
