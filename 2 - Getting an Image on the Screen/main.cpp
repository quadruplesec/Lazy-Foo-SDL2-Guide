#include <SDL2/SDL.h>
#include <iostream>

// Screen Dimension constants
const int SCREEN_WIDTH = 307;
const int SCREEN_HEIGHT = 295;

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

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
        gWindow = SDL_CreateWindow("The Witch of Miracles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (gWindow == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }
        else
        {
            // Get Window Surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
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
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

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
            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

            // Update surface
            SDL_UpdateWindowSurface(gWindow);
        }
    }

    // Hack to get window to stay up (DISGUSTING)
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    // Free resources and close SDL
    close();

    return 0;
}