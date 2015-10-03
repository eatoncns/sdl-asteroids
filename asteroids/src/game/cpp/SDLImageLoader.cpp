#include <SDLImageLoader.hpp>
#include <SDLImage.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

namespace pjm
{
    SDLImageLoader::SDLImageLoader(SDL_Renderer* iRenderer)
        : _renderer(iRenderer)
    {}

    shared_ptr<Renderable> SDLImageLoader::loadFromFile(const std::string& iFilePath)
    {
        image_map::iterator it = _images.find(iFilePath);
        if (it != _images.end())
        {
            image_map::value_type imagePair = *it;
            return imagePair.second;
        }
        return loadNewImage(iFilePath);
    }


    shared_ptr<Renderable> SDLImageLoader::loadNewImage(const std::string& iFilePath)
    {
        SDL_Texture* texture = NULL;
        int width = 0;
        int height = 0;
        SDL_Surface* loadedSurface = IMG_Load(iFilePath.c_str());
        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", 
                   iFilePath.c_str(), 
                   IMG_GetError());
            return shared_ptr<Renderable>();
        }
        else
        {
            texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
            if (texture == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", 
                       iFilePath.c_str(), 
                       SDL_GetError());
                return shared_ptr<Renderable>();
            }
            width = loadedSurface->w;
            height = loadedSurface->h;
            SDL_FreeSurface(loadedSurface);
        }
        _images[iFilePath] = make_shared<SDLImage>(_renderer, texture, width, height); 
        return _images[iFilePath];

    }
}
