#include <SDLKeyConvert.hpp>

namespace pjm
{
    ShipAction SDLKeyConvert(const Uint8* iState)
    {
        ShipAction action;
        if (iState[SDL_SCANCODE_UP])
        {
            action.accelerate = true;
        }
        if (iState[SDL_SCANCODE_LEFT] && !iState[SDL_SCANCODE_RIGHT])
        {
            action.turn_left = true;
        }
        if (iState[SDL_SCANCODE_RIGHT] && !iState[SDL_SCANCODE_LEFT])
        {
            action.turn_right = true;
        }
        if (iState[SDL_SCANCODE_SPACE])
        {
            action.shoot = true;
        }
        return action;
    }
}
