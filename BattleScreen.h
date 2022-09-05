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
#include "BattleButton.h"
#include "BattleEffects.h"
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

    bool battleFinished = false;
    bool quit = false;
    bool herosTurn = true;

    SDL_Texture* nameTexture;
    SDL_Rect nameRect;

    CharacterAnimationSet heroAnimationSet;
    CharacterAnimationSet enemyAnimationSet;

    HPBar heroHP;
    HPBar enemyHP;

    BattleButton fightButton;
    BattleButton itemButton;

    int heroDmg = 0, enemyDmg = 0;

    BattleEffects battleEffects;    

    BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType);
    ~BattleScreen();

    bool animationsPlaying();
    void update();
    void draw();
};