#include <iostream>
#include <string>
#include "Animal.h"
#include "Narwhal.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

int main(int argc, char **argv) {
    // Initialise SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // if init not return 0, then initialisation failed
        cout << "SDL Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    // initialise subsystems we need e.g sdl image, mixer, ttf
    // TODO: look up C++ bitwise logic
    // image- being able to deal with other image types other than bmp. Also lets you play with surface pixel data
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        cout << "SDL Img Init Error: " << IMG_GetError() << endl;
        return 1;
    }
    // ttf - text to font, for rendering text to screen
    if(TTF_Init() != 0)
    {
        cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
        return 1;
    }
    // mixer - sound and music
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("RPG GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        cout << "SDL Window Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr)
    {
        cout << "SDL Renderer Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    bool keepLooping = true;
    // Game Loop
    while(keepLooping)
    {
        SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255); // RGB (e.g R = 0-255)
        // clear entire screen with current draw colour
        SDL_RenderClear(renderer);

        SDL_Rect rect;
        rect.x = 10;
        rect.y = 10;
        rect.w = 50;
        rect.h = 50;
        SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);
        // draws filled in rectangle to window using rectangles data
        SDL_RenderFillRect(renderer, &rect);

        // swaps drawing buffer
        SDL_RenderPresent(renderer);

        // ticks are milliseconds since the start of SDL init
        if(SDL_GetTicks() > 5000) // 1000ms = 1second
        {
            keepLooping = false;
        }
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    cout << "end of code" << endl;

    return 0; 
}