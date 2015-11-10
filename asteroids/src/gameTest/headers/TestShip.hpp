#ifndef _PJM_TESTSHIP_HPP_
#define _PJM_TESTSHIP_HPP_

#include <Ship.hpp>
#include <ShipAction.hpp>
#include <ScreenWrapper.hpp>
#include <TestImageLoader.hpp>
#include <Rectangle.hpp>
#include <list>

struct TestShip : public pjm::Ship
{
    TestShip();

    bool initialise(const pjm::Vector& iInitialLocation,
                    pjm::ImageLoader& iImageLoader);

    boost::shared_ptr<pjm::Bullet> update(const pjm::ShipAction& iAction,
                                          unsigned int iTimeElapsed);

    pjm::Rectangle getBoundingBox();

    void render();

    void collideWith(pjm::Asteroid* iAsteroid);

    bool isExpired();

    int renderCalls;
    std::list<pjm::Vector> initialiseCalls;
    std::list<pjm::Asteroid*> collideCalls;
    bool initialiseSuccess;
    bool expired;
    pjm::Rectangle boundingBox;
    boost::shared_ptr<pjm::Bullet> bullet;
    static TestImageLoader imageLoader;
    static boost::shared_ptr<pjm::ScreenWrapper> screenWrapper;
    static boost::shared_ptr<pjm::BulletLoader> bulletLoader;
};

#endif
