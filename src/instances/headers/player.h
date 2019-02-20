//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "../../controllers/headers/gameController.h"

bool canPlayerMoveToCell(Object *player, int y, int x);
void movePlayerToCell(Object *player,int y, int x);
void playerInterfaceController(Object *player , char key);
void playerPlaintTheBomb(Object *player,int y, int x);
#endif //BOMBERMAN_PLAYER_H
