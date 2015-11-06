#include <SDLKeyConvert.hpp>
#include <gmock/gmock.h>
#include <algorithm>

using namespace pjm;
using ::testing::Eq;

class SDLKeyConvertTest : public ::testing::Test
{
    protected:
        SDLKeyConvertTest()
        {
            std::fill(input, input+SDL_NUM_SCANCODES, 0);
        }

        Uint8 input[SDL_NUM_SCANCODES];
        ShipAction result;
};

TEST_F(SDLKeyConvertTest, ConvertsUpKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    result.accelerate = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, ConvertsLeftKeyPress)
{
    input[SDL_SCANCODE_LEFT] = 1;
    result.turn_left = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, ConvertsRightKeyPress)
{
    input[SDL_SCANCODE_RIGHT] = 1;
    result.turn_right = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, ConvertsUpLeftKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    input[SDL_SCANCODE_LEFT] = 1;
    result.accelerate = true;
    result.turn_left = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, ConvertsUpRightKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    result.accelerate = true;
    result.turn_right = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, LeftAndRightTogetherCancelOut)
{
    input[SDL_SCANCODE_LEFT] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, LeftAndRightTogetherCancelOutLeavingOthers)
{
    input[SDL_SCANCODE_LEFT] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    input[SDL_SCANCODE_UP] = 1;
    result.accelerate = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, UnknownKeysMapToNone)
{
    input[SDL_SCANCODE_COMMA] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}

TEST_F(SDLKeyConvertTest, ConvertsSpaceKey)
{
    input[SDL_SCANCODE_SPACE] = 1;
    result.shoot = true;
    EXPECT_THAT(SDLKeyConvert(input), Eq(result));
}
