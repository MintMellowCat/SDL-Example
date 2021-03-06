#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>

const Uint32 fps = 60; //Set speed in fps (frames per second)
const Uint32 minframetime = 1000 / fps;

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN); //Display window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //Create renderer

    SDL_SetWindowFullscreen(window, 0);

    bool running = true;
    Uint32 frametime;
    SDL_Event event;

    while (running) //This is called once per frame
    {
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set background color

        SDL_SetWindowResizable(window, SDL_TRUE); //Make window resizable

        SDL_RenderClear(renderer); //Clear screen

        static bool fullScreen = true; //Is fullscreen
        static int windowWidth = 1000; 	//Get window width
        static int windowHeight = 700; //Get window height
        static int screenWidth = 1920;
        static int screenHeight = 1080;

        const Uint8* state = SDL_GetKeyboardState(NULL); //Store key state in variable
 
        SDL_RenderPresent(renderer); //Render everything
        
        frametime = SDL_GetTicks(); //Get frame time

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_F11) { //Detect if F11 is pressed
                    if (fullScreen) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_RestoreWindow(window);
                        SDL_SetWindowSize(window, windowWidth, windowHeight);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); //Toggle fullscreen off

                        fullScreen = false;
                    }
                    else {
                        SDL_SetWindowSize(window, 1920, 1080);
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); //Toggle fullscreen on

                        fullScreen = true;

                        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
                    }
                }
            }

            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                }
            }

            if (SDL_QUIT == event.type) //Detect if user presses the x button
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);

                break; //Quit game
            }
        }

        if (SDL_GetTicks() - frametime < minframetime) //Check if it is running at the right speed
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));

    }

	return 0;
}