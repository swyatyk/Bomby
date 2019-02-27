//
// Created by Sviatoslav Prylutsky on 2/5/19.
//


#include "headers/player.h"
#include "headers/map.h"
#include "headers/bomb.h"
#include "headers/cell.h"

void playerInterfaceController(Object *player , char key)
{
    pthread_t thread;
    switch(key)
    {
        case 'w':
            movePlayerToCell(player,player->posY-1 , player->posX);
            break;
        case 's':
            movePlayerToCell(player,player->posY+1 , player->posX);
            break;
        case 'd':
            movePlayerToCell(player,player->posY , player->posX+1);
            break;
        case 'a':
            movePlayerToCell(player,player->posY , player->posX-1);
            break;
        case 'b':
            if (pthread_create(&thread, NULL, playerPlaintTheBomb, player) != 0) {
                printf("main error: can't create thread \n");
            }
            break;
        default:
            printf("\n Wrong key %c \n",key);
            break;
    }

}

void movePlayerToCell(Object *player,int y, int x){
    if(canPlayerMoveToCell(player,y,x))
    {
        removeObjFromCell(player,player->posY,player->posX);
        addObjToCell(player,y,x);
        printMaps();
    }

}


bool canPlayerMoveToCell(Object *player, int y, int x) {
    Object *currentCell = getCell(y,x);
    Object *currentObject = currentCell;
    while(currentObject->next){
        Object *tmp = currentObject->next;
        if(tmp->type == WALL || tmp->type == BLOCK){;
            return false;
        }
        currentObject = tmp;

    }
    return true;
}

