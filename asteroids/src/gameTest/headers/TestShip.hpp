#ifndef _PJM_TESTSHIP_HPP_
#define _PJM_TESTSHIP_HPP_

#include <Ship.hpp>
#include <ShipAction.hpp>
#include <Rectangle.hpp>
#include <Vector.hpp>
#include <list>

class TestShip : public pjm::Ship
{
    public:
        TestShip();

        void willShootBullet(boost::shared_ptr<pjm::FixedSpeedBullet> iBullet);

        bool initialise(const pjm::Vector& iInitialLocation,
                        pjm::ImageLoader& iImageLoader);

        boost::shared_ptr<pjm::FixedSpeedBullet> update(const pjm::ShipAction& iAction,
                                              unsigned int iTimeElapsed);

        void render();

        pjm::Rectangle getBoundingBox();


        void collideWith(pjm::Asteroid* iAsteroid);

        bool isExpired();

        int renderCalls;
        std::list<pjm::Vector> initialiseCalls;
        std::list<pjm::Asteroid*> collideCalls;
        bool initialiseSuccess;
        bool expired;
        pjm::Rectangle boundingBox;

    private:
        boost::shared_ptr<pjm::FixedSpeedBullet> _bullet;
};

#endif
