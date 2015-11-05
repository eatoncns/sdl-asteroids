#include <SDLKeyConvert.hpp>

namespace pjm
{
    keyboard::KeyPress SDLKeyConvert(const Uint8* iState)
    {
        keyboard::KeyPress keyPress = keyboard::NONE;
        if (iState[SDL_SCANCODE_UP])
        {
            keyPress = keyboard::UP;
            if (iState[SDL_SCANCODE_LEFT] && !iState[SDL_SCANCODE_RIGHT])
            {
                keyPress = keyboard::UP_LEFT;
            }
            else if (iState[SDL_SCANCODE_RIGHT] && !iState[SDL_SCANCODE_LEFT])
            {
                keyPress = keyboard::UP_RIGHT;
            }
        }
        else if (iState[SDL_SCANCODE_LEFT] && !iState[SDL_SCANCODE_RIGHT])
        {
            keyPress = keyboard::LEFT;
        }
        else if (iState[SDL_SCANCODE_RIGHT] && !iState[SDL_SCANCODE_LEFT])
        {
            keyPress = keyboard::RIGHT;
        }
        return keyPress;
    }
}
