#include <SDLGame.hpp>
#include <SDL2/SDL.h>
#include <GameElements.hpp>
#include <SDLImageLoader.hpp>

namespace pjm
{
    SDLGame::SDLGame(const ScreenInfo& iScreenInfo)
        : _screenInfo(iScreenInfo),
          _window(NULL),
          _renderer(NULL),
          _running(false),
          _imageLoader(NULL),
          _gameElements(NULL)
    {}

    
    SDLGame::~SDLGame()
    {
        if (_window != NULL)
        {
            if (_renderer != NULL)
            {
                if (_gameElements != NULL)
                {
                    delete _gameElements;
                }
                if (_imageLoader != NULL)
                {
                    delete _imageLoader;
                }
                SDL_DestroyRenderer(_renderer);
                _renderer = NULL;
            }
            SDL_DestroyWindow(_window);
            _window = NULL;
        }
        SDL_Quit();
    }

    
    bool SDLGame::initialise()
    {
        if (!initSDL())
        {
            return false;
        }
        if (!initWindow())
        {
            return false;
        }
        if (!initRenderer())
        {
            return false;
        }
        if (!initGameElements())
        {
            return false;
        }
        startGame();
        return true;
    }

    
    bool SDLGame::initSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        return true;
    }

    
    bool SDLGame::initWindow()
    {
        _window = SDL_CreateWindow(_screenInfo.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   _screenInfo.width, _screenInfo.height, SDL_WINDOW_SHOWN);
        if (_window == NULL)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        return true;
    }


    bool SDLGame::initRenderer()
    {
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (_renderer == NULL)
        {
            printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        return true;
    }


    bool SDLGame::initGameElements()
    {
        _imageLoader = new SDLImageLoader(_renderer);
        _gameElements = new GameElements(*_imageLoader, _screenInfo);
        return _gameElements->initialise();
    }

    
    void SDLGame::startGame()
    {
        _running = true;
    }


    bool SDLGame::isRunning()
    {
        return _running;
    }


    void SDLGame::update(unsigned int iTimeElapsed)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                _running = false;
            }
        }
    }


    void SDLGame::draw()
    {
        _gameElements->render();
        SDL_RenderPresent(_renderer);
    }

}
