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
            float reductionFactor = sqrt(MAX_VELOCITY/velocitySquared);
            _velocity *= reductionFactor;
        }
    }

    void Ship::updateLocation(unsigned int iTimeElapsed)
    {
        _location += _velocity*iTimeElapsed;
        if (_location.y < 0)
        {
            _location.y += _bounds.y;
        }
        else if (_location.y > _bounds.y)
        {
            _location.y -= _bounds.y;
        }
        if (_location.x < 0)
        {
            _location.x += _bounds.x;
        }
        else if (_location.x > _bounds.x)
        {
            _location.x -= _bounds.x;
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
