#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* sdl_window = nullptr;
SDL_Surface* sdl_screen_surface = nullptr;
SDL_Surface* sdl_stretched_surface = nullptr;


enum key_press_surfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


SDL_Surface* gkey_press_surfaces[KEY_PRESS_SURFACE_TOTAL];


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        sdl_window = SDL_CreateWindow("Kihihihihi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (sdl_window == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }
        else
        {
            sdl_screen_surface = SDL_GetWindowSurface(sdl_window);
        }
    }

    return true;
}


SDL_Surface* load_surface(std::string filename)
{
    SDL_Surface* loaded_surface = SDL_LoadBMP(filename.c_str());

    if (loaded_surface == nullptr)
    {
        std::cout << "Image could not be created! SDL_Error: " << SDL_GetError() << '\n';
    }

    return loaded_surface;
}


bool load_media()
{
    gkey_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("a_toast.bmp");
    
    if (gkey_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
    {
        std::cout << "Failed to load default image!\n";
        return false;
    }

    gkey_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("diavolo.bmp");

    if (gkey_press_surfaces[KEY_PRESS_SURFACE_UP] == nullptr)
    {
        std::cout << "Failed to load default image!\n";
        return false;
    }

    gkey_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("fun_surprise.bmp");

    if (gkey_press_surfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
    {
        std::cout << "Failed to load DOWN image!\n";
        return false;
    }

    gkey_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("tewi.bmp");

    if (gkey_press_surfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
    {
        std::cout << "Failed to load LEFT image!\n";
        return false;
    }

    gkey_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("the_specimen.bmp");

    if (gkey_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
    {
        std::cout << "Failed to load RIGHT image!\n";
        return false;
    }

    return true;
}


void close()
{
    SDL_FreeSurface(sdl_stretched_surface);
    sdl_stretched_surface = nullptr;

    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;

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

    sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitSurface(sdl_stretched_surface, nullptr, sdl_screen_surface, nullptr);
    SDL_UpdateWindowSurface(sdl_window);

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
                        sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN:
                        sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                        break;

                    case SDLK_LEFT:
                        sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                        
                    case SDLK_RIGHT:
                        sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    default:
                        sdl_stretched_surface = gkey_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }

                SDL_BlitSurface(sdl_stretched_surface, nullptr, sdl_screen_surface, nullptr);
                SDL_UpdateWindowSurface(sdl_window);
            }
        }
    }

    close();
    return 0;
}