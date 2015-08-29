#include <gmock/gmock.h>
#include <Ship.hpp>
#include <Renderable.hpp>
#include <Coordinate.hpp>
#include <list>

using namespace pjm;
using ::testing::ElementsAre;

struct TestRenderable : public Renderable
{
    void render(Coordinate iLocation)
    {
        renderCalls.push_back(iLocation);
    }

    std::list<Coordinate> renderCalls;
};

TEST(ShipTest, RendersImageAtCurrentLocation)
{
    Coordinate initialLocation(5,5);
    TestRenderable shipImage;
    Ship ship(initialLocation, shipImage);
    ship.render();
    EXPECT_THAT(shipImage.renderCalls, ElementsAre(initialLocation));
}
