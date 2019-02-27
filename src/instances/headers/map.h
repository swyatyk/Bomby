//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "../../instances/headers/object.h"


typedef struct  {
    int mapSizeY;
    int mapSizeX;
    Object **cells;
}Map;

char **getCharMap();
void printMaps();
void initMapByObjects();
void printConsoleMap();
Map *getMapInstance();
void removeObjFromCell(Object *obj,int y, int x);
#endif //BOMBERMAN_MAP_H

