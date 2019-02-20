#include "bomberman.h"

void init_menuJoin(bomber* game)
{
//création menu pour rejoindre 
    game->pWindowMenuJoin = SDL_CreateWindow("Join a game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    if(game->pWindowMenuJoin){
        game->pRendererMenuJoin = SDL_CreateRenderer(game->pWindowMenuJoin, -1, SDL_RENDERER_ACCELERATED);
        if(!game->pRendererMenuJoin) {
            fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            exit(1);
        }
        create_menu_join(game);
    } else {
        fprintf(stderr, "Impossible de créer le fenetre SDL : %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
} 

void create_menu_join(bomber* game)
{
    game->pTextureMenuJoin = NULL;
    game->textIp = NULL;
    game->textPort = NULL;
    game->txtJoin = NULL;
    //game->userIp = NULL;
    //game->userPort = NULL;
    int font_size = 24;
    char * text = "Join a game";
    char * textIP = "Ip address : ";
    char * textPort = "Server port : ";

    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Surface* surface_textIp;
    SDL_Surface* surface_textPort;
    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);

    surface_background = SDL_LoadBMP("assets/img/main_menu.bmp");
    if ( !surface_background ){
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_text = TTF_RenderText_Solid(police, text, normalColor);
    if ( !surface_text ){
        fprintf(stdout,"Échec de chargement du text (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_textIp = TTF_RenderText_Solid(police, textIP, normalColor);
    if ( !surface_textIp ) {
        fprintf(stdout,"Échec de chargement du textIP (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_textPort = TTF_RenderText_Solid(police, textPort, normalColor);
    if ( !surface_textPort ) {
        fprintf(stdout,"Échec de chargement du textIP (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    TTF_CloseFont(police);
    
    game->pTextureMenuJoin = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_background);
    if ( !game->pTextureMenuJoin ){
        fprintf(stdout,"Échec de création de la textureMenuJoin - %s\n",SDL_GetError());
        game_destroy(game);
    }
    SDL_FreeSurface(surface_background);

    game->txtJoin = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_text);
    if (!game->txtJoin) {
        fprintf(stderr, "Impossible de charger  la texture txtJoin: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }

    game->textIp = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_textIp);
    if (!game->textIp) {
        fprintf(stderr, "Impossible de charger  la texture textIp: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
    game->textPort = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_textPort);
    if (!game->textPort) {
        fprintf(stderr, "Impossible de charger  la texture textIp: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }

    SDL_FreeSurface(surface_textIp);
    SDL_FreeSurface(surface_textPort);
}
