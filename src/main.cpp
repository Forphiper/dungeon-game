#include <iostream>
#include <string>
#include "Character.h"
#include "Hero.h"
#include "MapScreen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

int main(int argc, char **argv) {
    //output hello world to the screen
	//cout = console out
	cout << "Hello there..." << endl; //endl = end line
	cout << "What is your name?" << endl;
	//variable to hold name of user/player
	//format of declaring a variable: datatype variableName;
	string name;
	//read name into name variable from keyboard
	//cin = console in
	cin >> name;

	cout << "Welcome to the dungeon " << name << ", muahahahaha!!!" << endl;

	cout << "How old are you?" << endl;
	int age;
	cin >> age;
	cout << "So you are " << age << " years old!" << endl;

	cout << "What is your favourite number: " << endl;
	int favNum;
	cin >> favNum;
	cout << "Well you are now stuck in this dungeon for " << favNum << " years! Muahahaha!" << endl;
	
	//working out the new age
	int newAge = age + favNum;
	cout << "Its time to escape before you turn " << newAge << " years old!" << endl;

	//output warning if they'll be 80 or older
	if (newAge >= 80) 
	{
		cout << "You might not even live to this age!" << endl;
	}

	//if favNum is equal to 64 then output message
	if (favNum == 64) {
		cout << "Nice favourite number by the way!" << endl;
	}

	//hero stats
	int hp = 0, str = 0, def = 0, agi = 0;

	bool characterSetup = false;

	while (characterSetup == false)
	{
		cout << "What type of character are you?" << endl;
		cout << "1 - Beserker" << endl;
		cout << "2 - Buff Nut" << endl;
		cout << "3 - Speedy Ninja" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			hp = 60;
			str = 10;
			def = 2;
			agi = 3;
		}
		else if (choice == 2) {
			hp = 100;
			str = 4;
			def = 5;
			agi = 1;
		}
		else if (choice == 3) {
			hp = 80;
			str = 3;
			def = 1;
			agi = 10;
		}
		else
		{
			cout << "Invalid choice! Try again...." << endl;
		}

		if (choice >= 1 && choice <= 3)
		{
			characterSetup = true;
		}
	}

	cout << "Stats" << endl;
	cout << "hp: " << hp << endl;
	cout << "strength: " << str << endl;
	cout << "defense: " << def << endl;
	cout << "agility: " << agi << endl;

	cout << "The first gate is opening, counting down..." << endl;
	//   setup;    condition; incrementer/decrementer
	for (int i = 10; i >= 0; i--) {
		cout << i << "..." << endl;
	}
    Hero hero;
	hero.setName(name);
	hero.setupStats(hp, str, def, agi);
    
    /*
    string name;
    name = "phiper";
    int hp = 0, str = 0, def = 0, agi = 0;
    hp = 30;
    def = 2;
    str = agi = 5;

    Hero hero;
    hero.setName(name);
    hero.setupStats(hp, str, def, agi);
    hero.displayStats();
    */

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

    SDL_Window* window = SDL_CreateWindow("RPG GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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

    // the size gfx are at min, but then scale up to actual window size
    SDL_RenderSetLogicalSize(renderer, 320, 240);
    
    // load up image file and store as Texture inside of gfx card VRAM
    SDL_Texture* testImg = IMG_LoadTexture(renderer, "../assets/girlIdle.png");
    if(testImg == nullptr)
    {
        cout << "Image did not load! " << IMG_GetError() << endl;
    }
    // ITEMS(using arrays...)
    // items as ints. 0 = no item, 1 = chocolate, 2 = grenade, 3 = atk up, 4 = def up
    // integer array holding 10 int variables
    int items[10];
    // loop through array using for loop and set each slot to = 0 (no item)
    for(int i = 0; i < 10; i++)
    {
        items[i] = 0;
    }
    // set first item slot(index 0) to be our int number representing a chocolate
    // items[0] = 1;
    // items[1] = 1;
    // items[2] = 3;

    
    // setup mapscreen object
    MapScreen mapScreen(renderer, &hero, items);

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
        
        // the region of the texture we want to draw from
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = 107;
        srcRect.h = 137;

        // texture destination rectangle
        SDL_Rect destRect;
        destRect.x = 70;
        destRect.y = 20;
        destRect.w = 107;
        destRect.h = 137;

        // renderCopy renders textures to the window
        SDL_RenderCopy(renderer, testImg, &srcRect, &destRect);

        // update mapscreen
        mapScreen.update();

        if(mapScreen.quit)
            keepLooping = false;
        
        // draw game world
        mapScreen.draw();

        // swaps drawing buffer
        SDL_RenderPresent(renderer);

        // ticks are milliseconds since the start of SDL init
        // if(SDL_GetTicks() > 5000) // 1000ms = 1second
        // {
        //     keepLooping = false;
        // }

        
    }

    // Cleanup
    SDL_DestroyTexture(testImg);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0; 
}