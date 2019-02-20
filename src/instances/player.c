//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include "headers/player.h"
#include "headers/map.h"

void playerInterfaceController(Object *player , char key)
{
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
            playerPlaintTheBomb(player,player->posY , player->posX);
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
        //resloveCollapseConflicts(player);
    }

}


bool canPlayerMoveToCell(Object *player, int y, int x) {
    Object *currentCell = getCell(y,x);
    Object *currentObject = currentCell;
    while(currentObject->next){
        Object *tmp = currentObject->next;
        if(tmp->type == WALL || tmp->type == BLOCK){
            printf("player cant move to cell \n");
            return false;
        }
        currentObject = tmp;

    }
    return true;
}