#include <SDLImageLoader.hpp>
#include <SDLImage.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/foreach.hpp>

namespace pjm
{
    SDLImageLoader::SDLImageLoader(SDL_Renderer* iRenderer)
        : _renderer(iRenderer)
    {}


    SDLImageLoader::~SDLImageLoader()
    {
        BOOST_FOREACH(image_map::value_type imagePair, _images)
        {
            delete imagePair.second;
        }
    }


    Renderable* SDLImageLoader::loadFromFile(const std::string& iFilePath)
    {
        image_map::iterator it = _images.find(iFilePath);
        if (it != _images.end())
        {
            image_map::value_type imagePair = *it;
            return imagePair.second;
        }
        return loadNewImage(iFilePath);
    }


    Renderable* SDLImageLoader::loadNewImage(const std::string& iFilePath)
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
            return NULL;
        }
        else
        {
            texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
            if (texture == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", 
                       iFilePath.c_str(), 
                       SDL_GetError());
                return NULL;
            }
            width = loadedSurface->w;
            height = loadedSurface->h;
            SDL_FreeSurface(loadedSurface);
        }
        _images[iFilePath] = new SDLImage(_renderer, texture, width, height); 
        return _images[iFilePath];

    }
}
