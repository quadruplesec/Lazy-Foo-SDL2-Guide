#include <SDL2/SDL.h>
#include <iostream>

// Screen Dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
    // Window to render to
    SDL_Window* sdlWindow = nullptr;

    // Surface contained by the window
    SDL_Surface* sdlSurface = nullptr;

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }
    else
    {
        // Create window
        sdlWindow = SDL_CreateWindow("Kihihihihihi *cackle*cackle*cackle*", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (sdlWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return 1;
        }
        else
        {
            // Get window surface
            sdlSurface = SDL_GetWindowSurface(sdlWindow);

            // Fill the surface with white
            SDL_FillRect(sdlSurface, nullptr, SDL_MapRGB(sdlSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(sdlWindow);

            // Hack to get window to stay up
            SDL_Event e; 
            bool quit = false; 

            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }

	//Destroy window
	SDL_DestroyWindow(sdlWindow);

	//Quit SDL subsystems
	SDL_Quit();

    return 0;
}