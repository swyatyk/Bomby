//
// Created by Sviatoslav Prylutsky on 1/29/19.
//

#ifndef BOOMBERMAN_GAME_H
#define BOOMBERMAN_GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "../../instances/headers/object.h"

typedef struct {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *gameTileset;
    SDL_Texture *playerTileset;
    Object* player;


}Game;

void printGraphicMap(char *map);
void showScore( SDL_Renderer* Renderer, int score, int x, int y);
SDL_Rect getRectByCharValue(char value);
SDL_Texture * getTextureByCharValue(char value);
Game * gameInit();
Game * getGame();
void gameDestroy();

char getPressedKey();


#endif //BOOMBERMAN_GAME_H
