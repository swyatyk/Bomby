
#include "network/headers/server.h"
#include "config.h"
#include "controllers/headers/gameController.h"
#include "instances/headers/map.h"
#include "controllers/visualController.h"
#include "instances/headers/player.h"


int main3( int argc,  char *argv[] )
{

    initMap();
    initMutex();
    Game * game = gameInit();
    printGraphicMap();
    SDL_Delay(5000);
    gameDestroy();

    return EXIT_SUCCESS;
}

//int main(int argc, char *argv[])
int main()
{

    initMap();
    initMutex();
    Game * game = gameInit();
    Object *player1 = generateNewObject(11,5,5);
    addObjToCell(player1,1,1);
    printf("\n");
    printMaps();

    char c;
    printf("\nHello player your map mark position is (A) \n");
    printf("You can move your player with w,s,a,d keys \n");
    printf("plaint the bomb with b key \n");
    do{

        scanf("%c", &c);
        if(c!=10)
        {
            printf("\n");
            playerInterfaceController(player1,c);
            printMaps();
        }

    }
    while (c!='p');


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

    destroyMutex();

    return 1;
}

