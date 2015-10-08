#ifndef _PJM_LIFECOUNTER_HPP_
#define _PJM_LIFECOUNTER_HPP_

#include <boost/shared_ptr.hpp>
#include <Vector.hpp>

namespace pjm
{
    struct Renderable;
    struct ImageLoader;

    class LifeCounter
    {
        public:
            LifeCounter(const Vector& iInitialLocation,
                        int iInitialLives);

            bool initialise(ImageLoader& iImageLoader);

            void decrement();
            
            void render();

        private:
            boost::shared_ptr<Renderable> _image;
            Vector _location;
            int _numLives;
    };
}

#endif
