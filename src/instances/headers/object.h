//
// Created by Sviatoslav Prylutsky on 2/15/19.
//

#ifndef BOMBERMAN_OBJECT_H
#define BOMBERMAN_OBJECT_H

typedef enum{
    CELL,   // 0
    BLOCK,  // 1
    WALL,   // 2
    BOMB,   // 3
    OBJECT, // 4
    PLAYER, // 11,12,13,14
} Type;


typedef struct str_obj {

    Type type;

    struct str_obj* next;
    struct str_obj* last;
    //global object params what will be extended by childs
    int id;
    int textureId;
    int size;
    //
    int posY;
    int posX;
    int posW;
    int posH;
}Object;


Object *generateNewObject(int obj, int x, int y);

void setMyPosition();
void getMyPosition();
#endif //BOMBERMAN_OBJECT_H
