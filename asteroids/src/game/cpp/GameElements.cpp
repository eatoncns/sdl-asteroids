#include <GameElements.hpp>
#include <ImageLoader.hpp>

namespace pjm
{
    GameElements::GameElements(ImageLoader& iImageLoader,
                               const ScreenInfo& iScreenInfo)
        : _imageLoader(iImageLoader),
          _screenInfo(iScreenInfo)
    {}

    
    bool GameElements::initialise()
    {
        Renderable* shipImage = _imageLoader.loadFromFile("resources/Ship.gif");
        if (shipImage == NULL)
        {
            return false;
        }
        Coordinate initialShipLocation(_screenInfo.width/2, _screenInfo.height/2);
        _ship.reset(new Ship(initialShipLocation, *shipImage));
    }

    
    void GameElements::render()
    {
        _ship->render();
    }
}
