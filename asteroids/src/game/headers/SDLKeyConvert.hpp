#ifndef _PJM_SDLKEYCONVERT_HPP_
#define _PJM_SDLKEYCONVERT_HPP_

#include <KeyPress.hpp>
#include <SDL2/SDL.h>

namespace pjm
{
    ShipAction SDLKeyConvert(const Uint8* iState);
}

#endif /* end of include guard: _PJM_SDLKEYCONVERT_HPP_ */
