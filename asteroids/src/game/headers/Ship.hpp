#ifndef _PJM_SHIP_HPP_
#define _PJM_SHIP_HPP_

#include <boost/shared_ptr.hpp>

namespace pjm
{
    class Asteroid;
    class FixedSpeedBullet;
    class ImageLoader;
    class Rectangle;
    class ShipAction;
    class Vector;

    struct Ship
    {
        virtual bool initialise(const Vector& iInitialLocation,
                                ImageLoader& iImageLoader) = 0;

        virtual boost::shared_ptr<FixedSpeedBullet> update(const ShipAction& iAction,
                                                 unsigned int iTimeElapsed) = 0;

        virtual void render() = 0;

        virtual Rectangle getBoundingBox() = 0;

        virtual void collideWith(Asteroid* iAsteroid) = 0;

        virtual bool isExpired() = 0;

        virtual ~Ship() {}
    };
}

#endif /* end of include guard: _PJM_SHIP_HPP_ */
