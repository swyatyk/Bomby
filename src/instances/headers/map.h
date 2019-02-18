//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "../../controllers/headers/gameController.h"

typedef struct  {
    int mapSizeY;
    int mapSizeX;
    Cell **cells;
}Map;

void initMap();
void printMap();
Map *getMap();
Cell *getCell(int y, int x);
#endif //BOMBERMAN_MAP_H

