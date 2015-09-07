#ifndef _PJM_SDLIMAGE_HPP_
#define _PJM_SDLIMAGE_HPP_

#include <Renderable.hpp>

class SDL_Texture;
class SDL_Renderer;

namespace pjm
{
    struct Vector;

    class SDLImage : public Renderable
    {
        public:

            // N.b. SDLImage class is considered to take ownership
            //      of the contained texture
            SDLImage(SDL_Renderer* iRenderer, 
                     SDL_Texture* iTexture, 
                     int iWidth, int iHeight);

            ~SDLImage();

            void render(const Vector& iLocation, const double iAngle);

            int width();
            int height();

        private:
            SDL_Renderer* _renderer;
            SDL_Texture* _texture;
            int _width;
            int _height;
    };
}

#endif
