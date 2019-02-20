//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include "headers/bomb.h"
#include "headers/object.h"
#include "headers/cell.h"

void playerPlaintTheBomb(Object *player,int y, int x){

    Object *bomb = generateNewObject(3,player->posY,player->posX);
    addObjToCell(bomb,player->posY,player->posX);
}