//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include <stdlib.h>
#include "headers/cell.h"




void generateNewInstanceInCell(void **array , void *inst)
{
    array[0] = inst;
}

void generateNewBlockInCell(void **array , void *inst)
{
    array[0] = malloc(sizeof(inst));
}

int putInstanceToCell(Cell cell, int instance){
    Block block;
    Wall wall;

    switch (instance)
    {
        case 1:
            generateNewInstanceInCell(cell.blocks,malloc(sizeof(Block)));
            break;

        case 2:
            generateNewInstanceInCell(cell.walls,malloc(sizeof(Wall)));
            break;

        case 3:
            generateNewInstanceInCell(cell.bombs,malloc(sizeof(Wall)));
            break;
    }
}

