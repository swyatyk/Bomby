#include "bomberman.h"

void error(bomber* game, char* message)
{
    game->error = NULL;
    int font_size = 24;
    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Surface* surface_messageError;

    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);

    surface_messageError = TTF_RenderText_Solid(police, message, normalColor);
    if ( !surface_messageError ){
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    TTF_CloseFont(police);
    
    game->error = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_messageError);
    if ( !game->pTextureMenuJoin ){
        fprintf(stdout,"Échec de création de la textureMenuJoin - %s\n",SDL_GetError());
        game_destroy(game);
    }

    game->errorSize.x = 40;
    game->errorSize.y = 250;
    game->errorSize.w = 100;
    game->errorSize.h = 50;
    SDL_FreeSurface(surface_messageError);
}