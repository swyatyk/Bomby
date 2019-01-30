#include "../headers/bomberman.h"

SDL_Rect get_src_dest (int val, char* direction)
{
    SDL_Rect src;
    src.w = TILESET_SIZE;
    src.h = TILESET_SIZE;
    switch (val) {
    case (0) : //sol (herbe) 
        src.x = 3 * TILESET_SIZE;
        src.y = 0 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;
    case (1) ://Player 1
        if (strcmp(direction, "null") != 0) {
            src = get_src_animationPlayer1(direction);
        } else {
            src.x = 1 * TILESET_SIZE;
            src.y = 0 * TILESET_SIZE;
            src.w = TILESET_SIZE;
            src.h = TILESET_SIZE;
        }
        break;
        /*case (2) : //player 2          partie pas fait
        src.x = 1 * TILESET_SIZE;
        src.y = 1 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;      
    case (5) :
        src.x = 2 * TILESET_SIZE;
        src.y = 0 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;
    case (6) :
        src.x = 6 * TILESET_SIZE;
        src.y = 5 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;*/
    case (7) : // bloc incassable
        src.x = 1 * TILESET_SIZE;
        src.y = 0 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;
        /* case (8): // bloc cassable
        src.x = 2 * TILESET_SIZE;
        src.y = 0 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
    default: // bloc cassable
        src.x = 2 * TILESET_SIZE;
        src.y = 0 * TILESET_SIZE;
        src.w = TILESET_SIZE;
        src.h = TILESET_SIZE;
        break;
        };*/
    };
    return (src);
    }

SDL_Texture* get_texture(int val, bomber *game)
{    
    SDL_Texture* Shape = NULL;
    SDL_Surface *tileset;

    game->img_texture[1] = IMG_Load("./images/tileset_bomberman.bmp"); //fichier avec toutes les images de la map
    game->img_texture[2] = IMG_Load("./images/perso.bmp"); // fichier avec les images des perso
     
    if (val >= 1 && val <= 4) {     
        tileset = game->img_texture[2]; // cas des joueurs ( 1 à 4)
    } else {
        tileset = game->img_texture[1]; // cas de la map
    }
    if (!tileset) {
        fprintf(stderr, "Échec de chargement du sprite %s\n", SDL_GetError());
        game_destroy(game);
        return (NULL);
    } else {
        Shape = SDL_CreateTextureFromSurface(game->pRenderer, tileset);
        if (!Shape) {
            fprintf(stderr, "Échec de création de la texture %s\n", SDL_GetError());
            game_destroy(game);
            return (NULL);
        }
        SDL_FreeSurface(tileset);
    }
    return (Shape);
}


void init_map(bomber* game)
{
    int i;
    int j;
    int x = 0;
    int y = 0;
     int map[10][10] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {7, 1, 0, 0, 0, 0, 0, 0, 0, 7},
        {7, 0, 7, 0, 0, 7, 0, 7, 0, 7},
        {7, 0, 0, 0, 7, 0, 0, 0, 0, 7},
        {7, 0, 7, 0, 0, 0, 0, 7, 0, 7},
        {7, 0, 0, 0, 0, 7, 0, 0, 0, 7},
        {7, 0, 0, 7, 0, 0, 0, 7, 0, 7},
        {7, 0, 7, 0, 0, 7, 7, 0, 0, 7},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 7},
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7}};

    for(i=0; i < NOMBRE_BLOCS_LARGEUR; i++) {
        y = i * 50;
        for(j=0; j < NOMBRE_BLOCS_HAUTEUR; j++) {
            game->map[i][j] = map[i][j];
            x = j * 50;
            switch (game->map[i][j]) {
            case (0):
                game->textures[i][j] = get_texture(0, game); // prend la texture map
                break;
            case (1):
                game->player1Position.x = x;
                game->player1Position.y = y;
                game->textures[i][j] = get_texture(1, game); // prend la texture joueur
                break;
                /* case (8):
                game->textures[i][j] = get_texture(8, game);
                break;*/
            default:
                if (game->map[i][j] == 7)
                    game->textures[i][j] = get_texture(0, game); // prend la texture de la map
                break;
            }
        }
    }       
}
