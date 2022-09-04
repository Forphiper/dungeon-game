#include "BattleScreen.h"

BattleScreen::BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType)
{
    // if incorrect enemy type put in, default to glob
    if(enemyType != globType && enemyType != mimicType)
        enemyType = globType;

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

    // setup animations
    heroAnimationSet.setup(renderer, 47, 181, heroType);
    enemyAnimationSet.setup(renderer, 246, 114, enemyType);

    // revise polymorphism lessons from before if confused
    if(enemyType == globType)
        enemy = new Glob();
    else if(enemyType == mimicType)
        enemy = new Mimic();

    // setup health bars
    heroHP.setup(renderer, 90, 194);
    enemyHP.setup(renderer, 190, 10);

    // setup buttons
    fightButton.setup(renderer, { 0,180,80,30 }, "Fight");
    fightButton.selected = true;
    itemButton.setup(renderer, { 0,210,80,30 }, "Item");

    // decide who goes first
    if(hero->getAGI() > enemy->getAGI())
        herosTurn = true;
    else
        herosTurn = false;
}

BattleScreen::~BattleScreen()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(nameTexture);
}

bool BattleScreen::animationsPlaying()
{
    bool animating = heroAnimationSet.doAction || enemyAnimationSet.doAction;
    return animating;
}

void BattleScreen::update()
{
    // timing setup
    // deltaTime (measurement of time per frame render as fraction of 1 second e.g 0.5 = 500ms)
    float dt = 0;
    // last time we worked out deltaTime
    Uint32 lastUpdate = SDL_GetTicks();

    while(!battleFinished)
    {
        // update our delta time
        Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
        dt = timeDiff / 1000.0f;
        lastUpdate = SDL_GetTicks(); // update this so we get correct diff

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
                else if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    if(herosTurn)
                    {
                        fightButton.selected = true;
                        itemButton.selected = false;
                    }
                }
                else if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    if(herosTurn)
                    {
                        fightButton.selected = false;
                        itemButton.selected = true;
                    }
                }
                else if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE && sdlEvent.key.repeat == 0)
                {
                    if(herosTurn && !animationsPlaying())
                    {
                        if(fightButton.selected)
                        {
                            heroAnimationSet.doAttack();
                            enemyDmg = hero->getDamage();
                            herosTurn = false;
                        }
                    }
                }
            }
        }

        // exit battle if close window or press ESC
        if(quit)
            battleFinished = true;

        // update character states
        if(!animationsPlaying())
        {
            if(hero->getHP() <= 0 || enemy->getHP() <= 0)
            {
                // if anyone is dead, battle over
                battleFinished = true;
            }
            else if(heroDmg > 0)
            {
                hero->takeDamage(heroDmg);
                heroAnimationSet.doHit();

                heroDmg = 0;
            }
            else if(enemyDmg > 0)
            {
                enemy->takeDamage(enemyDmg);
                enemyAnimationSet.doHit();

                enemyDmg = 0;
            }
            else if(!herosTurn)
            {
                // ENEMY ATTACK
                enemyAnimationSet.doAttack();
                heroDmg = enemy->getDamage();
                herosTurn = true;
            }
        }
        
        // update  animations
        heroAnimationSet.update(dt);
        enemyAnimationSet.update(dt);

        // update health bars
        heroHP.hp = hero->getHP();
        heroHP.hpMax = hero->getHPMax();
    
        enemyHP.hp = enemy->getHP();
        enemyHP.hpMax = enemy->getHPMax();
        


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

    // draw enemy
    enemyAnimationSet.draw();

    // draw hero
    heroAnimationSet.draw();

    // ui bottom bar
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect bottomUIBar = { 0, 180, 320, 60 }; // x,y,w,h
    SDL_RenderFillRect(renderer, &bottomUIBar);
    // draw border too
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bottomUIBar);

    // draw name
    SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);

    // draw HP bars
    heroHP.draw();
    enemyHP.draw();

    // draw buttons
    fightButton.draw();
    itemButton.draw();

    // present frame to screen
    SDL_RenderPresent(renderer);
}