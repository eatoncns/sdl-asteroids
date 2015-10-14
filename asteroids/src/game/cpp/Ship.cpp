#include <Ship.hpp>
#include <boost/assign.hpp>
#include <math.h>

using namespace boost::assign;
using std::string;
using std::map;
using std::set;
using boost::shared_ptr;

namespace pjm
{
    Ship::Ship(shared_ptr<ScreenWrapper> iScreenWrapper)
      : MovingObject(iScreenWrapper),
        _acceleration(0, 0)
    {}


    string Ship::imageFilePath()
    {
        return "resources/Ship.gif";
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
            double absTotal = fabs(sinAngle) + fabs(cosAngle);
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
            float velocityFactor = MAX_VELOCITY/sqrt(velocitySquared);
            _velocity *= velocityFactor;
        }
    }
}
