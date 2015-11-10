#ifndef _PJM_SHIPCREATOR_HPP_
#define _PJM_SHIPCREATOR_HPP_

#include <boost/shared_ptr.hpp>

namespace pjm
{
    class Ship;
    class ImageLoader;
    class ScreenWrapper;
    struct ScreenInfo;

    class ShipCreator
    {
        public:
            boost::shared_ptr<Ship> create(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                           ImageLoader& iImageLoader,
                                           const ScreenInfo& iScreenInfo);

        private:
            virtual boost::shared_ptr<Ship> makeShip(boost::shared_ptr<ScreenWrapper> iScreenWrapper,
                                                     ImageLoader& iImageLoader,
                                                     const ScreenInfo& iScreenInfo);
    };
}

#endif
