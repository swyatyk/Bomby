#include "../headers/bomberman.h"

void game_movePlayer(bomber* game, SDL_Keycode direction)
{
    int x = game->player1Position.x / 50;
    int y = game->player1Position.y / 50;
    game->map[y][x] = 0; // met à 0 pour changer la texture du joueur en texture en map
    game->textures[game->player1Position.y /50][game->player1Position.x / 50] = game->textures[y][x];
    game->textures[y][x] = get_texture(0, game);
    //game->map[game->player1Position.y / 50][game->player1Position.x / 50] = 0;
    
    if (direction == SDLK_UP && game->map[(game->player1Position.y / 50) - 1][game->player1Position.x / 50] !=7) {
        game->player1Position.y = (y - 1) * 50;
        game->map[game->player1Position.y / 50][game->player1Position.x / 50] = 1; // met a 1 l'emplacement nouveau du joueur sur la map pour changer la texture map en joueur
    } else if (direction == SDLK_DOWN  && game->map[(game->player1Position.y / 50) + 1][game->player1Position.x / 50] != 7) {
        game->player1Position.y = (y + 1) * 50 ;
        game->map[game->player1Position.y / 50][game->player1Position.x / 50] = 1;
    } else if (direction == SDLK_LEFT  && game->map[game->player1Position.y / 50][(game->player1Position.x / 50) - 1]  != 7) {
        game->player1Position.x = (x - 1) * 50;
        game->map[game->player1Position.y / 50][game->player1Position.x / 50] = 1;
    } else if (direction == SDLK_RIGHT  && game->map[game->player1Position.y / 50][(game->player1Position.x / 50) + 1] != 7) {
        game->player1Position.x = (x + 1) * 50;
        game->map[game->player1Position.y / 50][game->player1Position.x / 50] = 1;
    } else
        game->map[y][x] = 1; // si on rentre dans un mur incassable remet la position actuel à 1 car il peut pas bouger
    game->textures[game->player1Position.y / 50][game->player1Position.x / 50] = get_texture(1, game);
}

