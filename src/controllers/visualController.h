//
// Created by Sviatoslav Prylutsky on 1/29/19.
//

#ifndef BOOMBERMAN_GAME_H
#define BOOMBERMAN_GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

typedef struct {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *gameTileset;
    SDL_Texture *playerTileset;


}Game;

void printGraphicMap();
Game * gameInit();
void gameDestroy();


#endif //BOOMBERMAN_GAME_H
