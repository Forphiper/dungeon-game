#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Hero.h"
#include "MapObject.h"
#include <list> // is a container that can shrink and grow (others vector, map, queue, stack)

#include <fstream> // file stream
#include "InfoBox.h"

#include <stdlib.h> // useful functions including rand and srand
#include <time.h> // time in seconds since start of year

#include "BattleScreen.h"

using namespace std;

class MapScreen
{
public:
    Hero* hero; // reference hero built inside main.cpp
    int* items; // going to use this to reference items[10] from main.cpp

    SDL_Renderer* renderer;

    enum {WALL, LAND};
    enum {HERO = 1, DOOR = 2, GLOB = 3, MIMIC = 4, CHEST = 5};
    enum {NOITEM, CHOCOLATE, GRENADE, ATKUP, DEFUP};

    // 2d array representing the map. 0 values = walls, 1 values = can walk/ground
    int map[10][10];
    MapObject heroObj;
    MapObject door;
    list<MapObject> mapObjects;

    SDL_Texture *heroTexture, *doorTexture, *globTexture, *chestTexture;

    bool quit = false;
    bool escaped = false;
    bool doorLocked = true;

    InfoBox infoBox;

    MapScreen(SDL_Renderer* renderer, Hero* hero, int* items);
    ~MapScreen();

    void itemFound();

    void update();
    void draw();
};