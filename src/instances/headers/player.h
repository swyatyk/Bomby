//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H


#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "object.h"

bool canPlayerMoveToCell(Object *player, int y, int x);
void movePlayerToCell(Object *player,int y, int x);
void playerInterfaceController(Object *player , char key);
char* convertScore(int score);
#endif //BOMBERMAN_PLAYER_H
