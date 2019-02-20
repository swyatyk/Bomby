
#include "network/headers/server.h"
#include "config.h"
#include "controllers/headers/gameController.h"
#include "instances/headers/map.h"

//int main(int argc, char *argv[])
int main()
{
    initMap();
    printMap();

    Object *player1 = generateNewObject(13,1,2);
    addObjToCell(player1,1,2);
    printf("\n");
    printMap();

    movePlayerToCell(player1,1,3);
    printf("\n");
    printMap();

    movePlayerToCell(player1,1,4);
    printf("\n");
    printMap();


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



    return 1;
}

