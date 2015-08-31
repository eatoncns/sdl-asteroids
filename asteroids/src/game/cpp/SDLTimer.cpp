#include <SDLTimer.hpp>
#include <SDL2/SDL.h>

namespace pjm
{
    unsigned int SDLTimer::getTime()
    {
        return SDL_GetTicks();
    }
}
