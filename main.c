#include "bomberman.h"

int main()
{
    bomber* game = game_init();
    init_menu(game);
    int quit = 0;
    char * ip_server = NULL;
    //init_map(game);
    while (quit != -1) {         
        quit = game_event(game);
        SDL_Delay(20);
        if (strcmp(game->choiceGame, "join") == 0){
            ip_server = writeIp(game);
            printf("%s", ip_server);
        }
    }
    game_destroy(game);
    return 0;
}
