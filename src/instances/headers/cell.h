//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_CELL_H
#define BOMBERMAN_CELL_H
#include "../../controllers/headers/gameController.h"
#include "player.h"

typedef struct{
    int showedId;
    int viewId;
    Player **players; //instance[instanceId][viewId]
    Bomb **bombs;
    Wall **walls;
    Block **blocks;
}Cell;

int putInstanceToCell(Cell c, Int i);
#endif //BOMBERMAN_CELL_H
