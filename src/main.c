
#include "network/headers/server.h"
#include "network/headers/client.h"
#include "config.h"
#include "instances/headers/map.h"
#include "gui/headers/gui.h"
#include "instances/headers/player.h"
#include "instances/headers/cell.h"


int main(int argc, char *argv[]){

   // Co_params param =  getMenuResponse();
   /*if(params.choise==HEBERGER)
       startServer();*/
/*    gameInit();
    while(1)
    {
        getPressedKey();
    }*/
    //gameInit();
    //getCharMap();
    initMapByObjects();
    printConsoleMap();
    startServer();
   //startClient("1234","127.0.0.1");
   //startClient(params.ip,params.port);
}

//int main(int argc, char *argv[])
int mainLocalCLient()
{

    initMapByObjects();
    initMutex();
    Game * game = gameInit();
    Object *player1 = generateNewObject(11,5,5);
    addObjToCell(player1,1,1);
    printf("\n");
    printMaps();

    //char c;
    printf("\nHello player your map mark position is (A) \n");
    printf("You can move your player with w,s,a,d keys \n");
    printf("plaint the bomb with b key \n");
/*    do{

        scanf("%c", &c);
        if(c!=10)
        {
            printf("\n");
            playerInterfaceController(player1,c);
            printMaps();
        }


    }
    while (c!='p')*/;



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

