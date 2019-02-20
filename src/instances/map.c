//
// Created by Sviatoslav Prylutsky on 2/5/19.
//



#include "headers/map.h"

void newCell(int mapParam,  int pY ,int pX);


int configMap[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
        gameMap -> cells = calloc(gameMap -> mapSizeY, sizeof(Object**)); // 10 == X dimension

        for(int y = 0; y<10; y++)
        {
            gameMap -> cells[y] = calloc(gameMap -> mapSizeX,sizeof(Object));
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


void printMap(){
    system("clear");
    Map *map = getMap();

    for(int y = 0 ; y < map->mapSizeY;y++)
    {
        for (int x = 0; x < map->mapSizeX; ++x)
        {
            //for visual better visual debug
            switch (getCell(y,x)->last->textureId)
            {
                case 0:
                printf(" %c",'.');
                break;

                case 11:
                printf(" %c",'A');
                break;

                case 12:
                printf(" %c",'B');
                break;

                case 13:
                printf(" %c",'C');
                break;

                case 14:
                printf(" %c",'D');
                break;

                default:
                printf(" %d",getCell(y,x)->last->textureId);
                break;
            }

        }
        printf("\n");
    }
}
