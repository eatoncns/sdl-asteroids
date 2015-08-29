#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Coordinate.hpp>
#include <TestRenderable.hpp>

using namespace pjm;
using ::testing::ElementsAre;


TEST(ShipTest, RendersImageAtCurrentLocation)
{
    Coordinate initialLocation(5,5);
    TestRenderable shipImage;
    Ship ship(initialLocation, shipImage);
    ship.render();
    EXPECT_THAT(shipImage.renderCalls, ElementsAre(initialLocation));
}
