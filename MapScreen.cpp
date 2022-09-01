#include "MapScreen.h"


MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{
    this->renderer = renderer;
    this->hero = hero;
    this->items = items;

    // loop through map using nested loop and clear all values out to be zero(walls)
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            map[x][y] = WALL;
        }
    }
    // manual room building
    // map[1][1] = 1;
    // map[2][1] = 1;
    // map[3][1] = 1;
    // map[1][2] = 1;
    // map[2][2] = 1;
    // map[3][2] = 1;

    // Open map text file
    fstream mapFile("assets/map.txt");
    if(mapFile.is_open())
    {
        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 10; x++)
            {
                // read in a single character from where we are up to in the file
                char grid;
                mapFile >> grid;
                if(grid == '0')
                {
                    map[y][x] = WALL; // wall
                }
                else
                {
                    map[y][x] = GROUND; // land

                    // TODO was it a hero, glob, chest or mimic
                    if(grid == 'h')
                    {
                        heroObj.type = HERO;
                        heroObj.x = x;
                        heroObj.y = y;
                    }
                    else if(grid == 'd')
                    {
                        door.type = DOOR;
                        door.x = x;
                        door.y = y;
                    }
                    else if(grid == 'c')
                    {
                        MapObject chest;
                        chest.type = CHEST;
                        chest.x = x;
                        chest.y = y;

                        mapObjects.push_back(chest);
                    }
                    else if(grid == 'g')
                    {
                        MapObject glob;
                        glob.type = GLOB;
                        glob.x = x;
                        glob.y = y;

                        mapObjects.push_back(glob);
                    }
                    else if(grid == 'm')
                    {
                        MapObject mimic;
                        mimic.type = MIMIC;
                        mimic.x = x;
                        mimic.y = y;

                        mapObjects.push_back(mimic);
                    }
                }
                
            }
        }
    }
    // close file
    mapFile.close();

    // LOAD UP TILE TEXTURES
    heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
    doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
    globTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
    chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");
}

MapScreen::~MapScreen()
{
    // CLEANUP TEXTURE MEMORY
    SDL_DestroyTexture(heroTexture);
    SDL_DestroyTexture(doorTexture);
    SDL_DestroyTexture(globTexture);
    SDL_DestroyTexture(chestTexture);
}

void MapScreen::draw()
{
    // MAP DRAWING
    // tile representing size of 1 grid thing from map
    SDL_Rect tileRect = {0, 0, 32, 32};
    // loop through and draw each grid value from map array
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            // IF is ground, set draw color to ground color
            // ELSE set to wall color
            if(map[y][x] == GROUND)
            {
                // ground
                SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
            }
            else
            {
                // walls
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            // MOVE rectangle to grid position with regards to tile width/height
            tileRect.x = x * tileRect.w;
            tileRect.y = y * tileRect.h;
            // draw rectangle to screen using current draw color
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }


    // DRAW MAP OBJECTS
    // draw hero
    tileRect.x = heroObj.x * tileRect.w;
    tileRect.y = heroObj.y * tileRect.h;
    SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);
    // draw door
    tileRect.x = door.x * tileRect.w;
    tileRect.y = door.y * tileRect.h;
    SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
    // DRAW MAP OBJECTS IN LIST
    // loop through list and draw each object
    for(MapObject mo: mapObjects)
    {
        // NOTE: mo is a mapObject copy from mapObjects and is not a direct reference to the mapObject in the list
        if(mo.active)
        {
            tileRect.x = mo.x * tileRect.w;
            tileRect.y = mo.y * tileRect.h;
            if(mo.type == GLOB) // glob
            {
                SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
            }
            else // mimic or chest
            {
                SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
            }
        }
    }
}



