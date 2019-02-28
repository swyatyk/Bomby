
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

    initMapByObjects();
   // getCharMap();
    //printConsoleMap();
    startServer();

   //startClient("1234","127.0.0.1");
   //startClient(params.ip,params.port);
}


