#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <Ship.hpp>
#include <boost/assign/list_of.hpp>
#include <map>

using namespace boost::assign;

namespace pjm
{
    GameElements::GameElements(ImageLoader& iImageLoader,
                               const ScreenInfo& iScreenInfo)
        : _shipCreator(&Ship::create),
          _ship(NULL),
          _imageLoader(iImageLoader),
          _screenInfo(iScreenInfo)
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
        _ship = _shipCreator(_imageLoader);
        Vector initialShipLocation(_screenInfo.width/2, _screenInfo.height/2);
        Vector screenBounds(_screenInfo.width, _screenInfo.height);
        return _ship->initialise(initialShipLocation, screenBounds);
    }


    typedef std::map<keyboard::KeyPress, Ship::Action> key_map_t;
    static const key_map_t key_to_action = map_list_of(keyboard::UP,   Ship::ACCELERATE)
                                                      (keyboard::LEFT, Ship::TURN_LEFT)
                                                      (keyboard::RIGHT, Ship::TURN_RIGHT)
                                                      (keyboard::UP_LEFT, Ship::ACCELERATE_LEFT)
                                                      (keyboard::UP_RIGHT, Ship::ACCELERATE_RIGHT)
                                                      (keyboard::NONE, Ship::NONE);

    void GameElements::update(keyboard::KeyPress iKeyPress, unsigned int iTimeElapsed)
    {
        key_map_t::const_iterator it = key_to_action.find(iKeyPress);
        if (it != key_to_action.end())
        {
            _ship->update(it->second, iTimeElapsed);
        }
    }

    
    void GameElements::render()
    {
        _ship->render();
    }
}
