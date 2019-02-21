
#include "network/headers/server.h"
#include "config.h"
#include "controllers/headers/gameController.h"
#include "instances/headers/map.h"

//int main(int argc, char *argv[])
int main()
{

    initMap();
    initMutex();
    Object *player1 = generateNewObject(11,5,5);
    addObjToCell(player1,1,1);
    printf("\n");
    printMap();

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
            printMap();
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

