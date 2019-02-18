//
// Created by Sviatoslav Prylutsky on 2/5/19.
//


#include "headers/map.h"

void newCell(int mapParam,  int pY ,int pX);


int mapGridTrue[10][10] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {7, 1, 0, 0, 0, 0, 0, 0, 0, 7},
        {7, 0, 7, 0, 0, 7, 0, 7, 0, 7},
        {7, 0, 0, 0, 7, 0, 0, 0, 0, 7},
        {7, 0, 7, 0, 0, 0, 0, 7, 0, 7},
        {7, 0, 0, 0, 0, 7, 0, 0, 0, 7},
        {7, 0, 0, 7, 0, 0, 0, 7, 0, 7},
        {7, 0, 7, 0, 0, 7, 7, 0, 0, 7},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 7},
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7}};
int configMap[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 11, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Map *getMap(){
    static Map *gameMap = NULL;
    if(gameMap == NULL){
        gameMap = malloc(sizeof(Map));
        gameMap -> mapSizeY = 10;
        gameMap -> mapSizeX = 10;
        gameMap -> cells = calloc(10, sizeof(Cell**)); // 10 == X dimension

        for(int y = 0; y<10; y++)
        {
            gameMap -> cells[y] = calloc(10,sizeof(Cell));
        }
    }

    return gameMap;
}

void initMap(){
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10;x++)
        {
            newCell(configMap[y][x],y,x);

            if(configMap[y][x]>0)
            {

               Object *tmp =  generateNewObject(configMap[y][x], y,x);
               addObjToCell(tmp,y,x);
            }
        }
    }
}
void addObjToCell(Object *obj,int y, int x) {
    Cell *currentCell = getCell(y, x);
    if (currentCell->innerObjectsCnt < currentCell->innerObjectsSize)
    {
        currentCell->innerObjects[currentCell->innerObjectsCnt] = obj;
        currentCell->innerObjectsCnt += 1;
    }

}

/*
 * This function return the higest @textureId
 * value of innerObjects elements
 *
 */

int sortCellShowPriority(Cell *cell)
{
    int viewId = 0;
    for(int i = 0 ; i < cell->innerObjectsCnt;i++)
    {
        int currCellViewId = cell->innerObjects[i]->textureId;
        if(viewId<currCellViewId)
        {

            viewId = currCellViewId;
        }
    }
    return viewId;
}


Cell *getCell(int y, int x){
    Map *map = getMap();
    Cell *cell = &map->cells[y][x];;
    cell->textureId = sortCellShowPriority(cell);
    return cell;
}
/*
 * This funtion , init the obj in the game
 * and reference them to SDL
 */
void newCell(int mapParam, int pY, int pX)
{

    Map *map = getMap();
    Cell *cell = malloc(sizeof(Cell));
    cell->textureId = 0; //  TEMPORARY DEBUG
    cell->posY = pY;
    cell->posX = pX;
    cell->innerObjectsCnt = 0;
    cell->innerObjectsSize = 5;
    cell->innerObjects = (Object**) calloc(cell->innerObjectsSize, sizeof(Object*)); // init 5 Objets, it must to be ok for start
    map->cells[pY][pX] = *cell;



}

void getView()
{
    /*for(){

    }*/
}

Object *generateNewObject(int typeId, int x, int y){

    Object *obj = (Object*)malloc(sizeof(Object));
    obj->textureId = typeId;
    obj->posX = x;
    obj->posY = y;

    switch (typeId)
    {
        case 0:
            obj->type = CELL;

            case 1:
            obj->type = BLOCK;
            break;

        case 2:
            obj->type = WALL;
            break;

        case 3:
            obj->type = BOMB;
            break;

        case 11:
            obj->type = PLAYER;
            obj->id = 1;
            break;

        case 12:
            obj->type = PLAYER;
            obj->id = 2;
            break;

        case 13:
            obj->type = PLAYER;
            obj->id = 3;
            break;

        case 14:
            obj->type = PLAYER;
            obj->id = 4;
            break;

        default:
            obj->type = OBJECT;
            obj->textureId =-1;
            break;
    }
    return obj;
}

void printMap(){

    Map *map = getMap();

    for(int y = 0 ; y < map->mapSizeY;y++)
    {
        for (int x = 0; x < map->mapSizeX; ++x)
        {
          printf(" %d",getCell(x,y)->textureId);
        }
        printf("\n");
    }
    //showMapContent();
}
