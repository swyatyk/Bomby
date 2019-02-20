//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include <zconf.h>
#include "headers/bomb.h"
#include "headers/object.h"
#include "headers/cell.h"
#include "headers/map.h"

void * playerPlaintTheBomb(void *args){
    Object *player = (Object*) args;
    Object *bomb = generateNewObject(3,player->posY,player->posX);
    addObjToCell(bomb,bomb->posY,bomb->posX);
    sleep(5);
    removeObjFromCell(bomb,bomb->posY,bomb->posX);
    printMap();
    free(bomb);
    return 0;
}