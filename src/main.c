
#include "network/headers/server.h"
#include "config.h"
#include "controllers/headers/gameController.h"
#include "instances/headers/map.h"

//int main(int argc, char *argv[])
int main()
{
    initMap();

    Object *player1 = generateNewObject(13,1,2);
    addObjToCell(player1,1,2);
    printf("\n");
    printMap();

    char c;
    printf("move your player w,s,a,d keys \n");
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



    return 1;
}

