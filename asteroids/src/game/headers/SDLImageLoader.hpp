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

            boost::shared_ptr<Renderable> loadFromFile(const std::string& iFilePath);

        private:
            typedef std::map<std::string, boost::shared_ptr<SDLImage> > image_map;
            image_map _images;
            SDL_Renderer* _renderer;

            boost::shared_ptr<Renderable> loadNewImage(const std::string& iFilePath);

            SDLImageLoader(const SDLImageLoader&);
            void operator=(const SDLImageLoader&);
    };
}

#endif
