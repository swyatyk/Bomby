#include "bomberman.h"

void init_menu(bomber* game)
{
//création menu
    game->pWindowMenu = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    if(game->pWindowMenu){
        game->pRendererMenu = SDL_CreateRenderer(game->pWindowMenu, -1, SDL_RENDERER_ACCELERATED);
        if(!game->pRendererMenu) {
            fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            exit(1);
        }
        Create_menu_render(game);
    } else {
        fprintf(stderr, "Impossible de créer le fenetre SDL : %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
}
void Create_menu_render(bomber* game)
{
    
    game->menuOn = 0;
    TTF_Init();
    //game->pRendererMenu = NULL;
    game->pTextureMenu = NULL;
    game-> texture_text = NULL;
    int font_size = 24;
    char * text = "Welcome to the Bomberman";
    char * txtjoin = "join a game";
    char * txthost = "host a game";
    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Surface* surface_join;
    SDL_Surface* surface_host;
    SDL_Surface* cursorGame;
    //SDL_Texture* texture;
    //SDL_Texture* texture_text;
    
    game->Menu.x = 0;
    game->Menu.y = 0;
    game->Menu.w = 500;
    game->Menu.h = 500;
    
    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);
    
    
    //SDL_RenderClear(game->pRendererMenu);
    //Ecriture des surfaces surfaces
    surface_background = SDL_LoadBMP("main_menu.bmp");
    if ( !surface_background ){
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_text = TTF_RenderText_Solid(police, text, normalColor);
    if ( !surface_text ) {
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_join = TTF_RenderText_Solid(police, txtjoin, normalColor);
    if ( !surface_join ) {
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_host = TTF_RenderText_Solid(police, txthost, normalColor);
    if ( !surface_host ) {
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
        game_destroy(game);
    }
    cursorGame = IMG_Load("bombe.png");
        if (!cursorGame) {
            fprintf(stderr, "Impossible de charger l'image bombe.png : %s\n", IMG_GetError());
            game_destroy(game);
            exit(1);
        } 
    //Libère la mémoire utilisé par la police
    TTF_CloseFont(police);
    
    game->pTextureMenu = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_background);
    if ( !game->pTextureMenu ){
        fprintf(stdout,"Échec de création de la texture1 - %s\n",SDL_GetError());
        game_destroy(game);
    }
    SDL_FreeSurface(surface_background);
    
    //text de départ
    game->startTxt.x = 60;
    game->startTxt.y = 30;
    game->startTxt.w = 300;
    game->startTxt.h = 50;
    
    //rejoidnre une game
    game->joingame.x = 40;
    game->joingame.y = 100;
    game->joingame.w = 150;
    game->joingame.h = 50;

    //héberger 
    game->hostGame.x = 40;
    game->hostGame.y = 170;
    game->hostGame.w = 150;
    game->hostGame.h = 50;

    game->cursorBomb.x = 200;
    game->cursorBomb.y = 100;
    game->cursorBomb.w = 50;
    game->cursorBomb.h = 50;

    // on copy sur le render le background
    game->texture_text = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_text);
    if ( !game->texture_text ) {
        fprintf(stdout,"Échec de création de la texture2 - %s\n",SDL_GetError());
        game_destroy(game);
    }

    game->ClientJoinGame = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_join);
    if ( !game->ClientJoinGame ) {
        fprintf(stdout,"Échec de création de la texture2 - %s\n",SDL_GetError());
        game_destroy(game);
    }

    game->ClientHostGame = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_host);
    if ( !game->ClientHostGame ) {
        fprintf(stdout,"Échec de création de la texture2 - %s\n",SDL_GetError());
        game_destroy(game);
    }
    game->cursor = SDL_CreateTextureFromSurface(game->pRendererMenu, cursorGame);
    if (!game->cursor) {
        fprintf(stderr, "Impossible de charger  la texture : %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
    SDL_FreeSurface(surface_host);
    SDL_FreeSurface(surface_join);
    SDL_FreeSurface(surface_text);
    SDL_FreeSurface(cursorGame);
    //SDL_DestroyTexture(texture);
    //SDL_DestroyTexture(texture_text);
   // TTF_Quit();

}