#include <SDLImage.hpp>
#include <SDL2/SDL.h>

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


    void SDLImage::render(const Coordinate& iLocation)
    {
        SDL_Rect renderQuad = {iLocation.x, iLocation.y, _width, _height};
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
