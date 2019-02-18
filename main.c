#include "bomberman.h"

int main()
{
    bomber* game = game_init();
    init_menu(game);
    int quit = 0;
    //init_map(game);
    while (quit != -1) {         
        quit = game_event(game);
        SDL_Delay(20);
    }
    game_destroy(game);
    return 0;
}
