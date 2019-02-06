//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include "../../controllers/headers/gameController.h"

struct {
    int maxClients;
    int mapSizeY;
    int mapSizeX;
    Cell **cells;
}Map;
#endif //BOMBERMAN_MAP_H

