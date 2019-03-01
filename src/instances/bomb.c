//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include <zconf.h>
#include <pthread.h>
#include <stdlib.h>
#include "headers/bomb.h"
#include "headers/object.h"
#include "headers/cell.h"
#include "headers/map.h"
#include "../network/headers/server.h"


pthread_mutex_t exploseBombMutex;

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
    sleep(1);
    bombs[0]->textureId = 20;
    getCell(bombs[0]->posY,bombs[0]->posX)->last = getProritaryAppairanceByObject(getCell(bombs[0]->posY,bombs[0]->posX));
    for(int i=1;i<5;i++)
    {
        if(bombs[i]!=NULL){
            addObjToCell(bombs[i],bombs[i]->posY,bombs[i]->posX);
        }
    }
    printMaps();
    notificateAllClients();
    sleep(1);
    for(int i=0;i<5;i++)
    {
        if(bombs[i]!=NULL) {
            explose(bombs[i]);
            removeObjFromCell(bombs[i], bombs[i]->posY, bombs[i]->posX);
            free(bombs[i]);
        }
    }
    free(bombs);
    notificateAllClients();
    printMaps();
    player->bombsCnt-=1;
    return 0;
}

void explose(Object *explosion)
{
    Object *targetCell = getCell(explosion->posY,explosion->posX);

   // pthread_mutex_lock(&exploseBombMutex);
    Object *current = targetCell;
    if(current->next)
    {
        while (current->next != NULL) {
            Object *tmp = current->next;
            if(current->type != BLOCK && current->type != CELL && current != explosion)
            {
                removeObjFromCell(current,current->posY,current->posX);
            }
            current = tmp;
        }

    }

  //  targetCell->last=getProritaryAppairanceByObject(targetCell);
  //  pthread_mutex_unlock(&exploseBombMutex);
}
