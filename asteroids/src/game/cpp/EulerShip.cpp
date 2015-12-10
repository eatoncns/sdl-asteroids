#include <BulletLoader.hpp>
#include <Rectangle.hpp>
#include <ScreenWrapper.hpp>
#include <EulerShip.hpp>
#include <ShipAction.hpp>

#include <math.h>

using std::string;
using boost::shared_ptr;

namespace pjm
{
    EulerShip::EulerShip(shared_ptr<ScreenWrapper> iScreenWrapper,
               shared_ptr<BulletLoader> iBulletLoader)
      : _angle(0.0),
        _acceleration(0, 0),
        _expired(false),
        _screenWrapper(iScreenWrapper),
        _bulletLoader(iBulletLoader)
    {}


    const string EulerShip::imageFilePath = "resources/Ship.gif";


    bool EulerShip::initialise(const Vector& iInitialLocation,
                          ImageLoader& iImageLoader)
    {
        _physicsData.location = iInitialLocation;
        return _renderer.initialise(iImageLoader, imageFilePath);
    }


    shared_ptr<Bullet> EulerShip::update(const ShipAction& iAction,
                                    unsigned int iTimeElapsed)
    {
        updateAngle(iAction, iTimeElapsed);
        updateAcceleration(iAction);
        updateVelocity(iTimeElapsed);
        updateLocation(iTimeElapsed);
        handleScreenWrap(iTimeElapsed);
        return handleShooting(iAction);
    }


    void EulerShip::updateAngle(const ShipAction& iAction, unsigned int iTimeElapsed)
    {
        double rotationDirection = iAction.turn_left  ? -1.0 :
                                   iAction.turn_right ?  1.0 :
                                                         0.0;
        double rotationUpdate = iTimeElapsed * ROTATION_FACTOR * rotationDirection;
        _angle += rotationUpdate;
    }


    void EulerShip::updateAcceleration(const ShipAction& iAction)
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


    void EulerShip::updateVelocity(unsigned int iTimeElapsed)
    {
        _physicsData.velocity = _physicsData.velocity + _acceleration*iTimeElapsed;
        float maxSquared = MAX_VELOCITY*MAX_VELOCITY;
        float velocitySquared = _physicsData.velocity.squareSum();
        bool maxVelocityExceeded = velocitySquared > maxSquared;
        if (maxVelocityExceeded)
        {
            float velocityFactor = MAX_VELOCITY/sqrt(velocitySquared);
            _physicsData.velocity *= velocityFactor;
        }
    }


    void EulerShip::updateLocation(unsigned int iTimeElapsed)
    {
        _physicsData.updateLocation(iTimeElapsed);
    }


    void EulerShip::handleScreenWrap(unsigned int iTimeElapsed)
    {
        _screenWrapper->wrap(_physicsData.location,
                             _physicsData.velocity,
                             iTimeElapsed);
    }


    shared_ptr<Bullet> EulerShip::handleShooting(const ShipAction& iAction)
    {
        return iAction.shoot
                 ? _bulletLoader->loadBullet(_physicsData.location, _angle)
                 : shared_ptr<Bullet>();
    }


    void EulerShip::render()
    {
        _renderer.renderAt(_physicsData.location, _angle);
    }


    Rectangle EulerShip::getBoundingBox()
    {
        return _renderer.getBoundingBox(_physicsData.location);
    }


    void EulerShip::collideWith(Asteroid* iAsteroid)
    {
        _expired = true;
    }


    bool EulerShip::isExpired()
    {
        return _expired;
    }
}
