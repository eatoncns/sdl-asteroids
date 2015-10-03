#include <gmock/gmock.h>
#include <ShipCreator.hpp>
#include <TestShip.hpp>
#include <ScreenInfo.hpp>

using namespace pjm;
using boost::shared_ptr;
using ::testing::ElementsAre;

struct TestableShipCreator : public ShipCreator
{
    TestableShipCreator()
        : testShip(new TestShip())
    {}

    shared_ptr<Ship> makeShip(shared_ptr<ScreenWrapper>)
    {
        return testShip;
    }

    shared_ptr<TestShip> testShip;
};

class ShipCreatorTest : public ::testing::Test
{
    protected:
        ShipCreatorTest()
            : screenInfo("Test", 200, 100)
        {}

        TestableShipCreator shipCreator;
        shared_ptr<ScreenWrapper> screenWrapper;
        TestImageLoader imageLoader;
        ScreenInfo screenInfo;
};

TEST_F(ShipCreatorTest, ReturnsShipWhenSuccessful)
{
    shared_ptr<Ship> ship = shipCreator.create(screenWrapper, imageLoader, screenInfo);
    EXPECT_TRUE(ship);
}

TEST_F(ShipCreatorTest, ReturnsNullSharedPtrWhenShipInitialiseFails)
{
    shipCreator.testShip->initialiseSuccess = false;
    shared_ptr<Ship> ship = shipCreator.create(screenWrapper, imageLoader, screenInfo);
    EXPECT_FALSE(ship);
}

TEST_F(ShipCreatorTest, InitialisesShipInCentreOfScreen)
{
    shipCreator.create(screenWrapper, imageLoader, screenInfo);
    EXPECT_THAT(shipCreator.testShip->initialiseCalls, ElementsAre(Vector(100, 50)));
}
