#ifndef _PJM_SDLIMAGELOADER_HPP_
#define _PJM_SDLIMAGELOADER_HPP_

#include <ImageLoader.hpp>
#include <map>

class SDL_Renderer;

namespace pjm
{
    class SDLImage;

    class SDLImageLoader : public ImageLoader
    {
        public:
            SDLImageLoader(SDL_Renderer* iRenderer);

            ~SDLImageLoader();

            // N.b. ownership of the pointer returned remains with
            //      the ImageLoader class
            Renderable* loadFromFile(const std::string& iFilePath);

        private:
            typedef std::map<std::string, SDLImage*> image_map;
            image_map _images;
            SDL_Renderer* _renderer;

            Renderable* loadNewImage(const std::string& iFilePath);

            // Prevent copying to avoid issues with ownership
            // of SDLImages
            SDLImageLoader(const SDLImageLoader&);
            void operator=(const SDLImageLoader&);
    };
}

#endif
