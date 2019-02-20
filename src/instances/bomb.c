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
    if(player->bombsCnt>0)
    {
        return 0;
    }
    player->bombsCnt+=1;
    Object **bombs = calloc(5, sizeof(Object*));
    int showParams[5] = {3,21,22,23,24};
    int positionYParams[5] = {0,-1,1,0,0};
    int positionXParams[5] = {0,0,0,-1,1};

    for(int i=0;i<5;i++)
    {
        bombs[i] = generateNewObject(showParams[i],player->posY+positionYParams[i],player->posX+positionXParams[i]);
    }
    addObjToCell(bombs[0],bombs[0]->posY,bombs[0]->posX);
    sleep(3);
    bombs[0]->textureId = 20;
    getCell(bombs[0]->posY,bombs[0]->posX)->last = getProritaryAppairanceByObject(getCell(bombs[0]->posY,bombs[0]->posX));
    for(int i=1;i<5;i++)
    {
        if(bombs[i]!=NULL){
            addObjToCell(bombs[i],bombs[i]->posY,bombs[i]->posX);
        }
    }
    printMap();
    sleep(2);
    for(int i=0;i<5;i++)
    {
        if(bombs[i]!=NULL) {
            removeObjFromCell(bombs[i], bombs[i]->posY, bombs[i]->posX);
            free(bombs[i]);
        }
    }
    free(bombs);
    printMap();
    player->bombsCnt-=1;
    return 0;
}
