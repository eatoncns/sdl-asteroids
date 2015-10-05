#include <GameElements.hpp>
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <map>

using boost::shared_ptr;
using std::list;
using namespace boost::assign;

namespace pjm
{
    GameElements::GameElements(shared_ptr<Ship> iShip,
                               list<shared_ptr<Asteroid> > iAsteroids)
        : _ship(iShip),
          _asteroids(iAsteroids),
          _collisionInteractions(new CollisionInteractions(_ship, _asteroids))
    {}


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
        BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
        {
            asteroid->update(iTimeElapsed);
        }
        _collisionInteractions->update();
    }

    
    void GameElements::render()
    {
        _ship->render();
        BOOST_FOREACH(shared_ptr<Asteroid> asteroid, _asteroids)
        {
            asteroid->render();
        }
    }
}
