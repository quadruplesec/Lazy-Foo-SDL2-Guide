#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gCurrentSurface = nullptr;


enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Kihihihihi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return true;
}


SDL_Surface* load_surface(std::string filename)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(filename.c_str());

    if (loadedSurface == nullptr)
    {
        std::cout << "Image could not be created! SDL_Error: " << SDL_GetError() << '\n';
    }

    return loadedSurface;
}


bool load_media()
{
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("a_toast.bmp");
    
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
    {
        std::cout << "Failed to load default image!\n";
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = load_surface("diavolo.bmp");

    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr)
    {
        std::cout << "Failed to load UP image!\n";
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("fun_surprise.bmp");

    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
    {
        std::cout << "Failed to load DOWN image!\n";
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("tewi.bmp");

    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
    {
        std::cout << "Failed to load LEFT image!\n";
        return false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("the_specimen.bmp");

    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
    {
        std::cout << "Failed to load RIGHT image!\n";
        return false;
    }

    return true;
}


void close()
{
    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}


int main(int argc, char* argv[])
{
    if (!init())
    {
        std::cout << "Failed to initisalise!\n";
        return 1;
    }

    if (!load_media())
    {
        std::cout << "Failed to load media!\n";
        return 1;
    }

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                break;   
            }

            // User presses a key
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;

                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                        
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    default:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }

                SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
    return 0;
}