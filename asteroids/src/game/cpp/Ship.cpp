#include <Ship.hpp>
#include <ShipAction.hpp>
#include <math.h>

using std::string;
using boost::shared_ptr;

namespace pjm
{
    Ship::Ship(shared_ptr<ScreenWrapper> iScreenWrapper)
      : ScreenWrappingObject(iScreenWrapper),
        _acceleration(0, 0)
    {}


    string Ship::imageFilePath()
    {
        return "resources/Ship.gif";
    }


    shared_ptr<Bullet> Ship::update(const ShipAction& iAction,
                                    unsigned int iTimeElapsed)
    {
        updateAngle(iAction, iTimeElapsed);
        updateAcceleration(iAction);
        updateVelocity(iTimeElapsed);
        updateLocation(iTimeElapsed);
        handleScreenWrap(iTimeElapsed);
        return shared_ptr<Bullet>();
    }


    void Ship::updateAngle(const ShipAction& iAction, unsigned int iTimeElapsed)
    {
        double rotationDirection = iAction.turn_left  ? -1.0 :
                                   iAction.turn_right ?  1.0 :
                                                         0.0;
        double rotationUpdate = iTimeElapsed * ROTATION_FACTOR * rotationDirection;
        _angle += rotationUpdate;
    }


    void Ship::updateAcceleration(const ShipAction& iAction)
    {
        if(iAction.accelerate)
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


    void Ship::collideWith(Asteroid* iAsteroid)
    {
        _expired = true;
    }
}
