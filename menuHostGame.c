#include "bomberman.h"

void init_menuHost(bomber* game)
{
//création menu pour rejoindre 
    game->pWindowMenuHost = SDL_CreateWindow("Join a game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    if(game->pWindowMenuHost){
        game->pRendererMenuHost = SDL_CreateRenderer(game->pWindowMenuHost, -1, SDL_RENDERER_ACCELERATED);
        if(!game->pRendererMenuHost) {
            fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            exit(1);
        }
        create_menu_host(game);
    } else {
        fprintf(stderr, "Impossible de créer le fenetre SDL : %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
} 

void create_menu_host(bomber* game)
{
    game->pTextureMenuHost = NULL;
    game->textPort = NULL;
    game->txtHost = NULL;
    int font_size = 24;
    char * text = "Host a game";
    char * textPort = "Server port : ";

    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Surface* surface_textPort;
    TTF_Font* police = TTF_OpenFont("../assets/arial.ttf", font_size);

    surface_background = SDL_LoadBMP("../assets/img/main_menu.bmp");
    if ( !surface_background ){
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_text = TTF_RenderText_Solid(police, text, normalColor);
    if ( !surface_text ){
        fprintf(stdout,"Échec de chargement du text (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_textPort = TTF_RenderText_Solid(police, textPort, normalColor);
    if ( !surface_textPort ) {
        fprintf(stdout,"Échec de chargement du textIP (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    TTF_CloseFont(police);
    
    game->pTextureMenuHost = SDL_CreateTextureFromSurface(game->pRendererMenuHost, surface_background);
    if ( !game->pTextureMenuHost ){
        fprintf(stdout,"Échec de création de la textureMenuHost - %s\n",SDL_GetError());
        game_destroy(game);
    }
    SDL_FreeSurface(surface_background);

    game->txtHost = SDL_CreateTextureFromSurface(game->pRendererMenuHost, surface_text);
    if (!game->txtHost) {
        fprintf(stderr, "Impossible de charger  la texture txtHost: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
    game->textPort = SDL_CreateTextureFromSurface(game->pRendererMenuHost, surface_textPort);
    if (!game->textPort) {
        fprintf(stderr, "Impossible de charger  la texture textIp: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
    SDL_FreeSurface(surface_text);
    SDL_FreeSurface(surface_textPort);
}


