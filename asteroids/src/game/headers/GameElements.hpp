#ifndef _PJM_GAMEELEMENTS_HPP_
#define _PJM_GAMEELEMENTS_HPP_

#include <ImageLoader.hpp> // TODO fwd declare when def in cpp
#include <ScreenInfo.hpp>
#include <Ship.hpp>
#include <boost/scoped_ptr.hpp>

namespace pjm
{
    // struct ImageLoader;

    class GameElements
    {
        public:
            GameElements(ImageLoader& iImageLoader,
                         const ScreenInfo& iScreenInfo)
                : _imageLoader(iImageLoader),
                  _screenInfo(iScreenInfo)
            {}

            bool initialise()
            {
                Renderable* shipImage = _imageLoader.loadFromFile("resources/Ship.gif");
                if (shipImage == NULL)
                {
                    return false;
                }
                Coordinate initialShipLocation(_screenInfo.width/2, _screenInfo.height/2);
                _ship.reset(new Ship(initialShipLocation, *shipImage));
            }

            void render()
            {
                _ship->render();
            }

        private:
            ImageLoader& _imageLoader;
            ScreenInfo _screenInfo;
            boost::scoped_ptr<Ship> _ship;
    };
}

#endif
