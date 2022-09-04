#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"
#include "CharacterType.h"
#include "CharacterAnimationSet.h"
#include "HPBar.h"
// TODO MORE

using namespace std;

class BattleScreen
{
public:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;

    Hero* hero;
    int* items; // pointer for our items array

    Character* enemy;

    bool battleFinished;
    bool quit;
    bool herosTurn;

    SDL_Texture* nameTexture;
    SDL_Rect nameRect;

    CharacterAnimationSet heroAnimationSet;
    CharacterAnimationSet enemyAnimationSet;

    HPBar heroHP;
    HPBar enemyHP;

    BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType);
    ~BattleScreen();

    void update();
    void draw();
};