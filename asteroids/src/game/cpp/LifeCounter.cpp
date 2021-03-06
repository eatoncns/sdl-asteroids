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
        _image = iImageLoader.loadFromFile("resources/Life.gif");
        return _image;
    }


    void LifeCounter::decrement()
    {
        if (_numLives > 0)
        {
            _numLives--;
        }
    }


    bool LifeCounter::gameOver()
    {
        return _numLives == 0;
    }
    
    
    void LifeCounter::render()
    {
        for (int i = 0; i < _numLives; ++i)
        {
            Vector renderLocation = _location + Vector(i*_image->width(), 0);
            _image->render(renderLocation, 0);
        }
    }
}
