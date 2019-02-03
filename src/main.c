#include "../headers/bomberman.h"
#include "../headers/server.h"

//int main(int argc, char *argv[])
int main()
{

   // int response = showMenu(); //return 1 if wanna to make server or return 2 if wanna to join the server else return 0 if somthing wrong
   /*if(response == 1 ){
       startServer();
       startClient();
   }else if(response == 2){
       startClinent();
   } else{
       printf("Player make the wrong choise!");
       exit(1);
   }*/

    startServer();

    return 1;
}



int startSDL()
{

    bomber* game = game_init();
    int quit = 0;
    init_map(game);
    while (quit != -1) {         
        quit = game_event(game);
        SDL_Delay(20);
    }
    game_destroy(game);
    return 0;
}
