//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_CELL_H
#define BOMBERMAN_CELL_H
#include "../../controllers/headers/gameController.h"
#include "../../instances/headers/object.h"





typedef struct {
    //global object params what will be extended by childs
    int textureId;
    //
    int posY;
    int posX;
    int posW;
    int posH;

    int innerObjectsCnt;
    int innerObjectsSize; //Size by default in malloc
    Object *innerObjects;

}Cell;

void addObjToCell(Object *obj, int x, int y);
#endif //BOMBERMAN_CELL_H
