#include <Ship.hpp>
#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <boost/assign.hpp>
#include <math.h>

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
        handleScreenWrap(iTimeElapsed);
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
        static const set<Action> accelerateActions = 
            list_of(ACCELERATE)(ACCELERATE_LEFT)(ACCELERATE_RIGHT);
        if(accelerateActions.find(iAction) != accelerateActions.end())
        {
            double angleRadians = _angle*M_PI/180.0;
            double sinAngle = sin(angleRadians);
            double cosAngle = cos(angleRadians);
            double absTotal = abs(sinAngle) + abs(cosAngle);
            double xProportion = sinAngle/absTotal;
            double yProportion = -cosAngle/absTotal; // - as SDL y axis is downwards
            _acceleration.x = xProportion*ACC_FACTOR;
            _acceleration.y = yProportion*ACC_FACTOR;
            return;
        }
        _acceleration.x = 0;
        _acceleration.y = 0;
    }


    void Ship::updateVelocity(unsigned int iTimeElapsed)
    {
        _velocity = _velocity + _acceleration*iTimeElapsed;
        float maxSquared = MAX_VELOCITY*MAX_VELOCITY;
        float velocitySquared = _velocity.squareSum();
        bool maxVelocityExceeded = velocitySquared > maxSquared;
        if (maxVelocityExceeded)
        {
            _velocity *= MAX_VELOCITY/sqrt(velocitySquared);
        }
    }

    
    void Ship::updateLocation(unsigned int iTimeElapsed)
    {
        _location += _velocity*iTimeElapsed;
    }
    

    void Ship::handleScreenWrap(unsigned int iTimeElapsed)
    {
        if (isOutsideOfScreen())
        {
            wrapLeftOrRight(iTimeElapsed) || 
            wrapTopOrBottom(iTimeElapsed);
        }
    }


    bool Ship::isOutsideOfScreen()
    {
        return (_location.x < 0 || _location.x > _bounds.x ||
                _location.y < 0 || _location.y > _bounds.y);
    }


    bool Ship::wrapLeftOrRight(unsigned int iTimeElapsed)
    {
        float inverseVelocityRatio = _velocity.y/_velocity.x;
        float intersectionX = _velocity.x > 0 ? 0 : _bounds.x; 
        float intersectionY = (inverseVelocityRatio*intersectionX) - (inverseVelocityRatio*_location.x) + _location.y;
        if (intersectionY > 0 && intersectionY < _bounds.y)
        {
            _location.x = intersectionX + _velocity.x*iTimeElapsed;
            _location.y = intersectionY + _velocity.y*iTimeElapsed;
            return true;
        }
        return false;
    }


    bool Ship::wrapTopOrBottom(unsigned int iTimeElapsed)
    {
        float velocityRatio = _velocity.x / _velocity.y;
        float intersectionY = _velocity.y > 0 ? 0 : _bounds.y;
        float intersectionX = (velocityRatio*intersectionY) - (velocityRatio*_location.y) + _location.x;
        if (intersectionX > 0 && intersectionX < _bounds.x)
        {
            _location.x = intersectionX + _velocity.x*iTimeElapsed;
            _location.y = intersectionY + _velocity.y*iTimeElapsed;
            return true;
        }
        return false;
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
