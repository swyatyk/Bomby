#include "../headers/bomberman.h"

SDL_Rect get_src_animationPlayer1(char* direction)
{
    int x = 0;
    SDL_Rect clip;
    if (strcmp(direction, "right") == 0) { 
        x = 7; // emplacement de l'mage du fichier Perso
        clip = get_moveByDirection(x);
    } else if (strcmp(direction, "left") == 0) {
        x = 3;
        clip = get_moveByDirection(x);
    } else if (strcmp(direction, "up") == 0) {
        x = 10 ;
        clip = get_moveByDirection(x);
    } else if (strcmp(direction, "down" ) == 0) {
        x = 1;
        clip = get_moveByDirection(x);
    }
    return (clip);
}

SDL_Rect get_moveByDirection(int size)
{
    SDL_Rect src;
    src.x = size * TILESET_SIZE;
    src.y = 0 * TILESET_SIZE;
    src.w = TILESET_SIZE;
    src.h = TILESET_SIZE;
    /* a voir plus tard pour les animations 
    src[1].x = (size+1) * TILESET_SIZE;
    src[1].y = 0 * TILESET_SIZE;
    src[1].w = TILESET_SIZE;
    src[1].h = TILESET_SIZE;
    */
    return (src);


}

void game_dropBombe(bomber* game)
{   

    bombe* bombe = NULL;
    bombe = malloc(sizeof(bombe));

    bombe->position.x = game->player1Position.x + 5;
    bombe->position.y = game->player1Position.y + 15;
    bombe->position.w = 35;
    bombe->position.h = 35;

    game->bombe = bombe;
    game->ifBombe = 1;
    

}

    
