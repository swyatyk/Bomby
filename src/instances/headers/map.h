//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "../../controllers/headers/gameController.h"

typedef struct  {
    int mapSizeY;
    int mapSizeX;
    Object **cells;
}Map;


void movePlayerToCell(Object *obj,int y, int x);
void initMap();
void printMap();
Map *getMap();
Object *getCell(int y, int x);
void removeObjFromCell(Object *obj,int y, int x);
#endif //BOMBERMAN_MAP_H

