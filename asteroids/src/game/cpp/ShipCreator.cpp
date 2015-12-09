#include <ShipCreator.hpp>
#include <EulerShip.hpp>
#include <SDLTimer.hpp>
#include <ImageLoader.hpp>
#include <ScreenWrapper.hpp>
#include <ScreenInfo.hpp>
#include <BulletLoader.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

namespace pjm
{
    shared_ptr<Ship> ShipCreator::create(shared_ptr<ScreenWrapper> iScreenWrapper,
                                         ImageLoader& iImageLoader,
                                         const ScreenInfo& iScreenInfo)
    {
        shared_ptr<Ship> ship = makeShip(iScreenWrapper, iImageLoader, iScreenInfo);
        Vector initialLocation(iScreenInfo.width/2, iScreenInfo.height/2);
        if (!ship->initialise(initialLocation, iImageLoader))
        {
            return shared_ptr<Ship>();
        }
        return ship;
    }

    shared_ptr<Ship> ShipCreator::makeShip(shared_ptr<ScreenWrapper> iScreenWrapper,
                                           ImageLoader& iImageLoader,
                                           const ScreenInfo& iScreenInfo)
    {
        Vector bounds(iScreenInfo.width, iScreenInfo.height);
        static SDLTimer timer;
        shared_ptr<BulletLoader> bulletLoader(new BulletLoader(bounds,
                                                               iImageLoader,
                                                               timer));
        return make_shared<EulerShip>(iScreenWrapper, bulletLoader);
    }
}
