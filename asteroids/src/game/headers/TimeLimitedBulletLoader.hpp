#ifndef _PJM_TIMELIMITEDBULLETLOADER_HPP_
#define _PJM_TIMELIMITEDBULLETLOADER_HPP_

#include <BulletLoader.hpp>
#include <Vector.hpp>

namespace pjm
{
    struct ImageLoader;
    struct Timer;
    class Bullet;

    class TimeLimitedBulletLoader : public BulletLoader
    {
        public:
            TimeLimitedBulletLoader(const Vector& iBounds,
                                    ImageLoader& iImageLoader,
                                    Timer& iTimer);

            boost::shared_ptr<Bullet> loadBullet(const Vector& iInitialLocation,
                                                 const double iAngle);

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

#endif
