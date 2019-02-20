//
// Created by Sviatoslav Prylutsky on 2/15/19.
//

#include <malloc.h>
#include "headers/object.h"
#include "headers/cell.h"


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
            break;

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

    targetCell->last=getProritaryAppairanceByObject(targetCell);
    targetCell->size +=1;
}

Object * getProritaryAppairanceByObject(Object *cell){
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
                    current->next = obj->next;
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

    targetCell->last=getProritaryAppairanceByObject(targetCell);
    targetCell->size -=1;
}