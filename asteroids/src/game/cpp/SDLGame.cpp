#include <SDLGame.hpp>
#include <SDL2/SDL.h>
#include <GameElements.hpp>
#include <LifeCounter.hpp>
#include <SDLImageLoader.hpp>
#include <KeyPress.hpp>
#include <Vector.hpp>
#include <ScreenWrapper.hpp>
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <ShipCreator.hpp>
#include <AsteroidCreator.hpp>
#include <LocationGenerator.hpp>
#include <RandomGeneratorImpl.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;
using std::list;

namespace pjm
{
    SDLGame::SDLGame(const ScreenInfo& iScreenInfo)
        : _screenInfo(iScreenInfo),
          _window(NULL),
          _renderer(NULL),
          _running(false)
    {}

    
    SDLGame::~SDLGame()
    {
        if (_window != NULL)
        {
            if (_renderer != NULL)
            {
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
        if (!(initSDL() &&
              initWindow() &&
              initRenderer() &&
              initGame()))
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
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
                printf( "Warning: Linear texture filtering not enabled!" );
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
        return true;
    }


    bool SDLGame::initGame()
    {
        return (initLifeCounter() && initGameElements());
    }

    
    bool SDLGame::initLifeCounter()
    {
        ImageLoader& imageLoader = getImageLoader();
        Vector initialLocation(10, 10);
        int initialLives(3);
        _lifeCounter.reset(new LifeCounter(initialLocation, initialLives));
        return _lifeCounter->initialise(imageLoader);
    }


    bool SDLGame::initGameElements()
    {
        ImageLoader& imageLoader = getImageLoader();
        Vector screenBounds(_screenInfo.width, _screenInfo.height);
        shared_ptr<ScreenWrapper> screenWrapper = make_shared<ScreenWrapper>(screenBounds);
        shared_ptr<Ship> ship = createShip(screenWrapper, imageLoader);
        list<shared_ptr<Asteroid> > asteroids = createAsteroids(screenWrapper, imageLoader);
        if (!ship || asteroids.empty())
        {
            return false;
        }
        _gameElements.reset(new GameElements(ship, asteroids));
        return true;
    }


    ImageLoader& SDLGame::getImageLoader()
    {
        static SDLImageLoader imageLoader(_renderer);
        return imageLoader;
    }


    shared_ptr<Ship> SDLGame::createShip(shared_ptr<ScreenWrapper> iScreenWrapper,
                                         ImageLoader& iImageLoader)
    {
        ShipCreator shipCreator;
        shared_ptr<Ship> ship = shipCreator.create(iScreenWrapper, iImageLoader, _screenInfo);
        return ship;
    }


    list<shared_ptr<Asteroid> > SDLGame::createAsteroids(shared_ptr<ScreenWrapper> iScreenWrapper,
                                                         ImageLoader& iImageLoader)
    {
        RandomGeneratorImpl random;
        LocationGenerator locationGenerator(_screenInfo, random);
        AsteroidCreator asteroidCreator;
        list<shared_ptr<Asteroid> > asteroids = asteroidCreator.create(iScreenWrapper,
                                                                       iImageLoader,
                                                                       locationGenerator,
                                                                       random);
        return asteroids;
    }

    
    void SDLGame::startGame()
    {
        _running = true;
    }


    bool SDLGame::isRunning()
    {
        return _running;
    }
    
    
    keyboard::KeyPress getKeyPress()
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        keyboard::KeyPress keyPress = keyboard::NONE;
        if (state[SDL_SCANCODE_UP])
        {
            keyPress = keyboard::UP;
            if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
            {
                keyPress = keyboard::UP_LEFT;
            }
            else if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT])
            {
                keyPress = keyboard::UP_RIGHT;
            }
        }
        else if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
        {
            keyPress = keyboard::LEFT;
        }
        else if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT])
        {
            keyPress = keyboard::RIGHT;
        }
        return keyPress;
    }


    void SDLGame::update(unsigned int iTimeElapsed)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                _running = false;
                return;
            }
        }
        keyboard::KeyPress keyPress = getKeyPress();
        bool shipCollision = _gameElements->update(keyPress, iTimeElapsed);
        if (shipCollision)
        {
            _lifeCounter->decrement();
            initGameElements();
            if (_lifeCounter->gameOver())
            {
                initLifeCounter();
            }
        }
    }


    void SDLGame::draw()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_renderer);
        _lifeCounter->render();
        _gameElements->render();
        SDL_RenderPresent(_renderer);
    }

}
