#include <LifeCounter.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>

namespace pjm
{
    LifeCounter::LifeCounter(const Vector& iInitialLocation,
                             int iInitialLives)
        : _location(iInitialLocation),
          _numLives(iInitialLives)
    {}

    bool LifeCounter::initialise(ImageLoader& iImageLoader)
    {
        _image = iImageLoader.loadFromFile("Life.gif");
        return _image;
    }
    
    void LifeCounter::render()
    {

    }
}
