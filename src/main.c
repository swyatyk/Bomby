
#include "network/headers/server.h"
#include "network/headers/client.h"
#include "config.h"
#include "instances/headers/map.h"
#include "gui/headers/gui.h"
#include "instances/headers/player.h"
#include "instances/headers/cell.h"
#include "gui/headers/menu_gui.h"


int main(int argc, char *argv[]){

    Menu *mainMenu = main_menu();
    ConnectionProps* param = (ConnectionProps*)malloc(sizeof(ConnectionProps));
    param = choiceMode(mainMenu);
    if(mainMenu->choice == 1)
    {
        SDL_HideWindow(mainMenu->Window);
        destroyMenu(mainMenu);
        gameInit();
        startClient(param->port, param->ip);
    }
    else if (mainMenu->choice == 2)
    {
        SDL_HideWindow(mainMenu->Window);
        destroyMenu(mainMenu);
        initMutex();
        startServer();
        destroyMutex();
    }
    destroyMenu(mainMenu);
    gameDestroy();

}


