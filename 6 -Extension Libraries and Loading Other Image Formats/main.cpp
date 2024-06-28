#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* sdl_displayed_surface = nullptr;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialised! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Nano desu~!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialise PNG loading
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("SDL_Image could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screen_surface = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface* load_surface(const char* path)
{
    SDL_Surface* optimised_surface = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(path);
    if (loaded_surface == nullptr)
    {
        printf("Unable to load image %s! SDL_Image Error: %s\n", path, IMG_GetError());
        return nullptr;
    }

    optimised_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);

    if (optimised_surface == nullptr)
    {
        printf("Unable to optimise image %s! SDL_Error: %s\n", path, SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loaded_surface);

    return optimised_surface;
}

void close_SDL()
{
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_FreeSurface(sdl_displayed_surface);
    sdl_displayed_surface = nullptr;
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        return 1;
    }

    sdl_displayed_surface = load_surface(argv[1]);

    if (sdl_displayed_surface == nullptr)
    {
        return 1;
    }

    SDL_Rect stretched_rect;
    stretched_rect.x = 0;
    stretched_rect.y = 0;
    stretched_rect.w = SCREEN_WIDTH;
    stretched_rect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(sdl_displayed_surface, nullptr, screen_surface, &stretched_rect);

    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    close_SDL();
    return 0;
}