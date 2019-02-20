//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include "headers/cell.h"
#include "headers/map.h"

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




