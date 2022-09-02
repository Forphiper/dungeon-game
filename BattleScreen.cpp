#include "BattleScreen.h"

BattleScreen::BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{
    this->renderer = renderer;
    this->hero = hero;
    this->items = items;

    // load background texture
    backgroundTexture = IMG_LoadTexture(renderer, "assets/bg.png");

    // Create Name Texture
    TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
    SDL_Color textColor = { 0,0,0,0 };
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, hero->getName().c_str(), textColor);
    nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    // setup name texture drawing destination rectangle
    nameRect.x = 90;
    nameRect.y = 180;
    SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);
}

BattleScreen::~BattleScreen()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(nameTexture);
}

void BattleScreen::update()
{
    while(!battleFinished)
    {
        // read user inputs including keyboard, mouse, gamepads, screen resize/close, touch screens etc
        SDL_Event sdlEvent;
        // loop through input events and copy their details one by one into our sdlEvent variable
        while(SDL_PollEvent(&sdlEvent))
        {
            // event when user clicks close window button
            if(sdlEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            // if a button was pressed
            if(sdlEvent.type == SDL_KEYDOWN)
            {
                // then check which button
                // did they press ESC key?
                if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        // exit battle if close window or press ESC
        if(quit)
            battleFinished = true;

        draw();
    }
}

void BattleScreen::draw()
{
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
    SDL_RenderClear(renderer);

    // draw bg
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // ui bottom bar
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect bottomUIBar = { 0, 180, 320, 60 }; // x,y,w,h
    SDL_RenderFillRect(renderer, &bottomUIBar);
    // draw border too
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bottomUIBar);


    // draw name
    SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);


    // present frame to screen
    SDL_RenderPresent(renderer);
}