#include <GameElements.hpp>
#include <ImageLoader.hpp>

namespace pjm
{
    GameElements::GameElements(ImageLoader& iImageLoader,
                               const ScreenInfo& iScreenInfo)
        : _imageLoader(iImageLoader),
          _screenInfo(iScreenInfo),
          _ship(NULL)
    {}


    GameElements::~GameElements()
    {
        if (_ship != NULL)
        {
            delete _ship;
            _ship = NULL;
        }
    }

    
    bool GameElements::initialise()
    {
        Renderable* shipImage = _imageLoader.loadFromFile("resources/Ship.gif");
        if (shipImage == NULL)
        {
            return false;
        }
        Vector initialShipLocation(_screenInfo.width/2, _screenInfo.height/2);
        _ship = new Ship(initialShipLocation, *shipImage);
        return true;
    }

    
    void GameElements::render()
    {
        _ship->render();
    }
}
