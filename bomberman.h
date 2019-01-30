


#ifndef _BOMBERMAN_H_
#define _BOMBERMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR_TILE 900
#define HAUTEUR_TILE 900
#define TILESET_SIZE 100

#define NOMBRE_BLOCS_LARGEUR 10
#define NOMBRE_BLOCS_HAUTEUR 10

typedef struct {
    // SDL_Texture* pTextureBombe;
    SDL_Rect position;
    int Timer;

} bombe;

typedef struct {
    
    //Variable SDL
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    int map[10][10];
    //Texture du jeu
    SDL_Texture* textures[10][10];
    SDL_Texture* pTexturePlayer;

    // images du jeu (bmp)
    SDL_Surface* img_texture[20];

    SDL_Rect player1Position;

    int ifBombe;
    bombe* bombe;

} bomber;


void game_dropBombe(bomber* game);

// init game
bomber* game_init();
void game_destroy(bomber* game);
void game_show(bomber* game, char* direction);
int game_event(bomber* game);

// partie map/player 
void init_map(bomber* game);
SDL_Texture* get_texture(int val, bomber* game);
SDL_Rect get_src_dest(int val, char* direction);
SDL_Rect get_src_animationPlayer1(char* direction);

// mouvement joueur
void game_movePlayer(bomber* game, SDL_Keycode direction);
SDL_Rect get_moveByDirection(int size);



#endif
