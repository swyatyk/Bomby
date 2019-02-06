//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include <stdlib.h>
#include "headers/cell.h"




void generateNewBlockInCell(Block **blocks , Block *block)
{
    blocks[sizeof(blocks)/ sizeof(block)+1] = (Block *) malloc(sizeof(block));
}

int getArraySize(void **arr){
    void *i;
    int size =0 ;
    while(i!=nul)
    {
        i = arr[i];
        size++;
    }
    return size;
}



int putInstanceToCell(Cell cell, int instance){
    Block block;
    Wall wall;

    switch (instance)
    {
        case 1:
            generateNewBlockInCell(cell.blocks,malloc(sizeof(Block)));
            break;

        case 2:
            generateNewWallInCell(cell.walls,malloc(sizeof(Wall)));
            break;

        case 3:
            generateNewInstanceInCell(cell.bombs,malloc(sizeof(Wall)));
            break;
    }
}

