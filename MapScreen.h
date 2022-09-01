#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Hero.h"
#include "MapObject.h"
#include <list> // is a container that can shrink and grow (others vector, map, queue, stack)

#include <fstream> // file stream

using namespace std;

class MapScreen
{
public:
    Hero* hero; // reference hero built inside main.cpp
    int* items; // going to use this to reference items[10] from main.cpp

    SDL_Renderer* renderer;

    enum MapType {WALL, LAND};
    enum ObjType {HERO = 1, DOOR = 2, GLOB = 3, MIMIC = 4, CHEST = 5};

    // 2d array representing the map. 0 values = walls, 1 values = can walk/ground
    int map[10][10];
    MapObject heroObj;
    MapObject door;
    list<MapObject> mapObjects;

    SDL_Texture *heroTexture, *doorTexture, *globTexture, *chestTexture;

    bool quit = false;

    // InfoBox infoBox;

    MapScreen(SDL_Renderer* renderer, Hero* hero, int* items);
    ~MapScreen();

    void update();
    void draw();
};