#include <SDL2/SDL.h>
#include <iostream>

// Screen Dimension constants
const int SCREEN_WIDTH = 307;
const int SCREEN_HEIGHT = 295;

//The window we'll be rendering to
SDL_Window* sdl_window = nullptr;
    
//The surface contained by the window
SDL_Surface* sdl_screen_surface = nullptr;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = nullptr;


// Starts up SDL and creates window
bool init()
{
    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        // Create window
        sdl_window = SDL_CreateWindow("The Witch of Miracles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (sdl_window == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }
        else
        {
            // Get Window Surface
            sdl_screen_surface = SDL_GetWindowSurface(sdl_window);
        }
    }

    return true;
}


// Loads media
bool load_media()
{
    // Load Splash Image
    gHelloWorld = SDL_LoadBMP("a_toast.bmp");

    if (gHelloWorld == nullptr)
    {
        std::cout << "Unable to load image! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }

    return true;
}


// Frees media and shuts down SDL
void close()
{
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    // Destroy window
    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;

    // Quit SDL Subsystems
    SDL_Quit();
}


int main(int argc, char* args[])
{
    // Start up SDL and create window
    if (!init())
    {
        std::cout << "Failed to initialise!\n";
        return 1;
    }
    else
    {
        // Load media
        if (!load_media())
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            // Apply image
            SDL_BlitSurface(gHelloWorld, nullptr, sdl_screen_surface, nullptr);

            // Update surface
            SDL_UpdateWindowSurface(sdl_window);
        }
    }

    bool quit = false;
    SDL_Event e;

    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}