#include <Ship.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <boost/assign.hpp>

using namespace std;
using namespace boost::assign;

namespace pjm
{
    Ship::Ship(ImageLoader& iImageLoader)
      : _location(0, 0),
        _velocity(0, 0),
        _acceleration(0, 0),
        _angle(0.0),
        _bounds(0,0),
        _imageLoader(iImageLoader),
        _image(NULL)
    {}
    

    bool Ship::initialise(const Vector& iInitialLocation, const Vector& iBounds)
    {
        _location = iInitialLocation;
        _bounds = iBounds;
        _image = _imageLoader.loadFromFile("resources/Ship.gif");
        return (_image != NULL);
    }
   

    void Ship::update(const Action iAction, unsigned int iTimeElapsed)
    {
        updateAngle(iAction, iTimeElapsed);
        updateAcceleration(iAction);
        updateVelocity(iTimeElapsed);
        updateLocation(iTimeElapsed);
    }


    void Ship::updateAngle(const Action iAction, unsigned int iTimeElapsed)
    {
        static const map<Action, double> rotationDirections = 
            map_list_of(TURN_LEFT, -1.0)
                       (TURN_RIGHT, 1.0)
                       (ACCELERATE_LEFT, -1.0)
                       (ACCELERATE_RIGHT, 1.0);
       
        map<Action, double>::const_iterator directionIt = rotationDirections.find(iAction);
        if (directionIt == rotationDirections.end())
        {
            return;
        }
        double rotationUpdate = iTimeElapsed * ROTATION_FACTOR * directionIt->second;
        _angle += rotationUpdate;
    }


    void Ship::updateAcceleration(const Action iAction)
    {
        if (Vector::eqValue(_velocity.y, MAX_VELOCITY))
        {
            _acceleration.y = 0;
            return;
        }
        static const set<Action> accelerateActions = 
            list_of(ACCELERATE)(ACCELERATE_LEFT)(ACCELERATE_RIGHT);
        if(accelerateActions.find(iAction) != accelerateActions.end())
        {
            _acceleration.y += ACC_FACTOR;
            return;
        }
        if (_acceleration.y > ACC_FACTOR)
        {
           _acceleration.y -= ACC_FACTOR;
           return;
        }
        _acceleration.y = 0;
    }


    void Ship::updateVelocity(unsigned int iTimeElapsed)
    {
        _velocity = _velocity + _acceleration*iTimeElapsed;
        if (_velocity.y > MAX_VELOCITY)
        {
            _velocity.y = MAX_VELOCITY;
        }
    }

    void Ship::updateLocation(unsigned int iTimeElapsed)
    {
        // Minus velocity as we consider origin to be at
        // top left of screen
        _location = _location - _velocity*iTimeElapsed;
        if (_location.y < 0)
        {
            _location.y += _bounds.y;
        }
        else if (_location.y > _bounds.y)
        {
            _location.y -= _bounds.y;
        }
    }
    
    
    void Ship::render()
    {
        static int widthOffset = _image->width() / 2;
        static int heightOffset = _image->height() / 2;
        float renderX = _location.x - widthOffset;
        float renderY = _location.y - heightOffset;
        Vector renderLocation(renderX, renderY);
        _image->render(renderLocation, _angle);
    }

    
    Ship* Ship::create(ImageLoader& iImageLoader)
    {
        return new Ship(iImageLoader);
    }
}
