


#ifndef _BOMBERMAN_H_
#define _BOMBERMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    char* str;
    int str_size;

} input_t;
typedef struct {

    input_t userWrite;
    int menuOn;
    char *choiceGame;
    int start;   
    //Variable SDL
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Window* pWindowMenu;
    SDL_Window* pWindowMenuJoin;
    SDL_Renderer* pRenderer;
    SDL_Renderer* pRendererMenu;
    SDL_Renderer* pRendererMenuJoin;
    int map[10][10];
    //Texture du jeu
    SDL_Texture* textures[10][10];
    SDL_Texture* pTexturePlayer;
    SDL_Texture* pTextureMenu;
    SDL_Texture* pTextureMenuJoin;
    SDL_Texture* ClientJoinGame;
    SDL_Texture* ClientHostGame;
    SDL_Texture* texture_text;
    SDL_Texture* cursor;
    SDL_Texture* txtJoin;
    SDL_Texture* textIp;
    SDL_Texture* userIp;
    // images du jeu (bmp)
    SDL_Surface* img_texture[20];

    SDL_Rect player1Position;
    SDL_Rect Menu;
    SDL_Rect startTxt;
    SDL_Rect joingame;
    SDL_Rect userTextIpJoin;
    SDL_Rect hostGame;
    SDL_Rect cursorBomb;
    int ifBombe;
    bombe* bombe;

} bomber;

void game_dropBombe(bomber* game);
void init_menu(bomber* game);
void menuScroll(char* scroll, bomber* game);
void init_menuJoin(bomber* game);
void draw_text(char *text, bomber* game);
// init game
bomber* game_init();
void create_game(bomber* game);
void game_destroy(bomber* game);
void game_show(bomber* game, char* direction);
int game_event(bomber* game);
void sendMess(char *ip, int port);

void create_menu_join(bomber* game);
char* writeIp(bomber* game);
void Create_menu_render(bomber* game);
// partie map/player 
void init_map(bomber* game);
SDL_Texture* get_texture(int val, bomber* game);
SDL_Rect get_src_dest(int val, char* direction);
SDL_Rect get_src_animationPlayer1(char* direction);

// mouvement joueur
void game_movePlayer(bomber* game, SDL_Keycode direction);
SDL_Rect get_moveByDirection(int size);



#endif
