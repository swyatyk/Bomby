//
// Created by Sviatoslav Prylutsky on 2/5/19.
//


#include <slcurses.h>
#include <stdbool.h>
#include "headers/map.h"

void newCell(int mapParam,  int pY ,int pX);


bool canPlayerMoveToCell(Object *pObj, int y, int x);

int configMap[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 11, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Map *getMap(){
    static Map *gameMap = NULL;
    if(gameMap == NULL){
        gameMap = malloc(sizeof(Map));
        gameMap -> mapSizeY = 10;
        gameMap -> mapSizeX = 10;
        gameMap -> cells = calloc(gameMap -> mapSizeY, sizeof(Object**)); // 10 == X dimension

        for(int y = 0; y<10; y++)
        {
            gameMap -> cells[y] = calloc(gameMap -> mapSizeX,sizeof(Object));
        }
    }

    return gameMap;
}

void initMap(){
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10;x++)
        {
            newCell(configMap[y][x],y,x);

            if(configMap[y][x]>0)
            {

                Object *tmp =  generateNewObject(configMap[y][x], y,x);
                addObjToCell(tmp,y,x);
            }
        }
    }
}
Object * getProritaryAppairance(Object *cell){
    Object *highter = cell;
    Object *current = cell->next;
    while(current)
    {
        if(current->textureId > highter->textureId)
        {
            highter = current;
        }

        Object *tmp = current->next;
        current = tmp;
    }
    return highter;
}

void addObjToCell(Object *obj,int y, int x) {

    Object *targetCell = getCell(y, x);
    Object *current = targetCell->next;
    obj->posY = targetCell->posY;
    obj->posX = targetCell->posX;

    if(current!=NULL)
    {
        while(current->next!=NULL)
        {
            Object *tmp = current->next;
            if(tmp->textureId < obj ->textureId)
            {
                break;
            }
            current = tmp;
        }
        if(current!=NULL)
        {
            Object *tmp = current->next;
            current->next = obj;
            obj->next = tmp;

        }
    }
    else
    {
        targetCell->next = obj;
    }

    targetCell->last=getProritaryAppairance(targetCell);
    targetCell->size +=1;
}



void removeObjFromCell(Object *obj,int y, int x)
{
    Object *targetCell = getCell(y, x);
    Object *current = targetCell;
    if(current->next)
    {
        while (current->next != NULL) {
            Object *tmp = current->next;
            if (tmp == obj)
            {
                if (tmp->next != NULL)
                {
                    *current->next = *obj->next;
                }
                else
                {
                    current->next = NULL;
                }
                obj->next = NULL;
            }
            current = tmp;
        }
    }

    targetCell->last=getProritaryAppairance(targetCell);
    targetCell->size -=1;
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
            return false;
        }
        currentObject = tmp;

    }
    return 0;
}

Object *getCell(int y, int x){
    Map *map = getMap();
    Object *cell = &map->cells[y][x];
    return cell;
}
/*
 * This funtion , init the obj in the game
 * and reference them to SDL
 */

void newCell(int mapParam, int pY, int pX)
{
    getMap()->cells[pY][pX] = *generateNewObject( mapParam,  pY,  pX);
}

Object *generateNewObject(int typeId, int y, int x){

    Object *obj = (Object*)malloc(sizeof(Object));
    obj->textureId = typeId;
    obj->posX = x;
    obj->posY = y;
    obj->last = obj;
    obj->size = 0;
    switch (typeId)
    {
        case 0:
            obj->type = CELL;
            obj->size = 0;

        case 1:
            obj->type = BLOCK;
            break;

        case 2:
            obj->type = WALL;
            break;

        case 3:
            obj->type = BOMB;
            break;

        case 11:
            obj->type = PLAYER;
            obj->id = 1;
            break;

        case 12:
            obj->type = PLAYER;
            obj->id = 2;
            break;

        case 13:
            obj->type = PLAYER;
            obj->id = 3;
            break;

        case 14:
            obj->type = PLAYER;
            obj->id = 4;
            break;

        default:
            obj->type = OBJECT;
            obj->textureId =-1;
            break;
    }
    return obj;
}

void printMap(){

    Map *map = getMap();

    for(int y = 0 ; y < map->mapSizeY;y++)
    {
        for (int x = 0; x < map->mapSizeX; ++x)
        {
            printf(" %d",getCell(y,x)->last->textureId);
        }
        printf("\n");
    }
}
