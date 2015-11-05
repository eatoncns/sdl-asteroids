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
};

TEST_F(SDLKeyConvertTest, ConvertsUpKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::UP));
}

TEST_F(SDLKeyConvertTest, ConvertsLeftKeyPress)
{
    input[SDL_SCANCODE_LEFT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::LEFT));
}

TEST_F(SDLKeyConvertTest, ConvertsRightKeyPress)
{
    input[SDL_SCANCODE_RIGHT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::RIGHT));
}

TEST_F(SDLKeyConvertTest, ConvertsUpLeftKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    input[SDL_SCANCODE_LEFT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::UP_LEFT));
}

TEST_F(SDLKeyConvertTest, ConvertsUpRightKeyPress)
{
    input[SDL_SCANCODE_UP] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::UP_RIGHT));
}

TEST_F(SDLKeyConvertTest, LeftAndRightTogetherCancelOut)
{
    input[SDL_SCANCODE_LEFT] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::NONE));
}

TEST_F(SDLKeyConvertTest, LeftAndRightTogetherCancelOutLeavingOthers)
{
    input[SDL_SCANCODE_LEFT] = 1;
    input[SDL_SCANCODE_RIGHT] = 1;
    input[SDL_SCANCODE_UP] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::UP));
}

TEST_F(SDLKeyConvertTest, UnknownKeysMapToNone)
{
    input[SDL_SCANCODE_COMMA] = 1;
    EXPECT_THAT(SDLKeyConvert(input), Eq(keyboard::NONE));
}
