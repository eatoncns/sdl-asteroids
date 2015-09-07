#include <SDLImage.hpp>
#include <SDL2/SDL.h>
#include <Vector.hpp>
#include <boost/math/special_functions/round.hpp>

using boost::math::iround;

namespace pjm
{
    SDLImage::SDLImage(SDL_Renderer* iRenderer,
                       SDL_Texture* iTexture,
                       int iWidth, int iHeight)
        : _renderer(iRenderer), _texture(iTexture),
          _width(iWidth), _height(iHeight)
    {}


    SDLImage::~SDLImage()
    {
        SDL_DestroyTexture(_texture);
    }


    void SDLImage::render(const Vector& iLocation,
                          const double iAngle)
    {
        SDL_Rect renderQuad = {iround(iLocation.x), iround(iLocation.y), 
                               _width, _height};
        SDL_RenderCopy(_renderer, _texture, NULL, &renderQuad);
    }


    int SDLImage::width()
    {
        return _width;
    }


    int SDLImage::height()
    {
        return _height;
    }
}
