#include "bomberman.h"

SDL_Renderer* Create_menu_render(SDL_Window * window, bomber* game){
    
    TTF_Init();
    game->pRendererMenu = NULL;
    int font_size = 24;
    char * text = "Press ENTER to start";
    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Rect Rect_dest;
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Texture* texture;
    SDL_Texture* texture_text;
    
    Rect_dest.x = 0;
    Rect_dest.y = 0;
    Rect_dest.w = 500;
    Rect_dest.h = 500;
    
    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);
    game->pRendererMenu = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_RenderClear(game->pRendererMenu);
    //Ecriture des surfaces surfaces
    surface_background = SDL_LoadBMP("main_menu.bmp");
    if ( !surface_background )
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
    
    surface_text = TTF_RenderText_Blended(police, text, normalColor);
    if ( !surface_text )
        fprintf(stdout,"Échec de chargement du texte (%s)\n",SDL_GetError());
    
    //Libère la mémoire utilisé par la police
    TTF_CloseFont(police);
    
    texture = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_background);
    if ( !texture )
        fprintf(stdout,"Échec de création de la texture1 - %s\n",SDL_GetError());
    
    SDL_FreeSurface(surface_background);
    
    
    // on copy sur le render le background
    SDL_RenderCopy(game->pRendererMenu, texture, NULL, &Rect_dest);
    
    Rect_dest.x = 100;
    Rect_dest.y = 30;
    Rect_dest.w = 300;
    Rect_dest.h = 50;
    
    // on copy sur le render le background
    texture_text = SDL_CreateTextureFromSurface(game->pRendererMenu, surface_text);
    if ( !texture_text )
        fprintf(stdout,"Échec de création de la texture2 - %s\n",SDL_GetError());
    
    SDL_RenderCopy(game->pRendererMenu, texture_text, NULL, &Rect_dest);
    SDL_FreeSurface(surface_text);
    
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_text);
    TTF_Quit();
    return game->pRendererMenu;
}