#include <GameElements.hpp>
#include <ImageLoader.hpp>
#include <RandomGeneratorImpl.hpp>
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <map>

using namespace boost::assign;

namespace pjm
{
    GameElements::GameElements(ImageLoader& iImageLoader,
                               const ScreenInfo& iScreenInfo)
        : _shipCreator(&Ship::create),
          _asteroidCreator(&Asteroid::create),
          _ship(NULL),
          _imageLoader(iImageLoader),
          _screenInfo(iScreenInfo),
          _screenWrapper(Vector(iScreenInfo.width, iScreenInfo.height))
    {}


    GameElements::~GameElements()
    {
        if (_ship != NULL)
        {
            delete _ship;
            _ship = NULL;
        }
        if (!_asteroids.empty())
        {
            BOOST_FOREACH(Asteroid* asteroid, _asteroids)
            {
                delete asteroid;
            }
        }
    }

    
    bool GameElements::initialise()
    {
        _ship = _shipCreator(_imageLoader, _screenWrapper);
        Vector initialShipLocation(_screenInfo.width/2, _screenInfo.height/2);
        if (!_ship->initialise(initialShipLocation))
        {
            return false;
        }
        static RandomGeneratorImpl random;
        for (int i = 0; i < NUM_ASTEROIDS; ++i)
        {
            Asteroid* asteroid = _asteroidCreator(_imageLoader, _screenWrapper, random);
            _asteroids.push_back(asteroid);
            if (!asteroid->initialise(Vector(100, 100)))
            {
                return false;
            }
        }
        return true;
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
        BOOST_FOREACH(Asteroid* asteroid, _asteroids)
        {
            asteroid->update(iTimeElapsed);
        }
    }

    
    void GameElements::render()
    {
        _ship->render();
        BOOST_FOREACH(Asteroid* asteroid, _asteroids)
        {
            asteroid->render();
        }
    }
}
