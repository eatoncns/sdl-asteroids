#include <SDLKeyConvert.hpp>

namespace pjm
{
    KeyboardState SDLKeyConvert(const Uint8* iState)
    {
        KeyboardState keyState;
        if (iState[SDL_SCANCODE_UP])
        {
            keyState.up = true;
        }
        if (iState[SDL_SCANCODE_LEFT] && !iState[SDL_SCANCODE_RIGHT])
        {
            keyState.left = true;
        }
        if (iState[SDL_SCANCODE_RIGHT] && !iState[SDL_SCANCODE_LEFT])
        {
            keyState.right = true;
        }
        if (iState[SDL_SCANCODE_SPACE])
        {
            keyState.space = true;
        }
        return keyState;
    }
}
