//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "../../instances/headers/object.h"
#include "../../controllers/headers/gameController.h"


typedef struct  {
    int mapSizeY;
    int mapSizeX;
    Object **cells;
}Map;

void playerInterfaceController(Object *player , char key);
void movePlayerToCell(Object *obj,int y, int x);
void initMap();
void printMap();
Map *getMap();
void removeObjFromCell(Object *obj,int y, int x);
#endif //BOMBERMAN_MAP_H
