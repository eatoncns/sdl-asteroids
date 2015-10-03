#include <ShipCreator.hpp>
#include <Ship.hpp>
#include <ImageLoader.hpp>
#include <ScreenWrapper.hpp>
#include <ScreenInfo.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

namespace pjm
{
    shared_ptr<Ship> ShipCreator::create(shared_ptr<ScreenWrapper> iScreenWrapper,
                                         ImageLoader& iImageLoader,
                                         const ScreenInfo& iScreenInfo)
    {
        shared_ptr<Ship> ship = makeShip(iScreenWrapper);
        Vector initialLocation(iScreenInfo.width/2, iScreenInfo.height/2);
        if (!ship->initialise(initialLocation, iImageLoader))
        {
            return shared_ptr<Ship>();
        }
        return ship;
    }

    shared_ptr<Ship> ShipCreator::makeShip(shared_ptr<ScreenWrapper> iScreenWrapper)
    {
        return make_shared<Ship>(iScreenWrapper);
    }
}
