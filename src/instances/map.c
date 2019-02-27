//
// Created by Sviatoslav Prylutsky on 2/5/19.
//



#include "headers/map.h"
#include "../gui/headers/gui.h"
#include "headers/cell.h"

void newCell(int mapParam,  int pY ,int pX);


int configMap[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
        {1, 0, 1, 2, 0, 1, 0, 1, 0, 1},
        {1, 2, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


char **getCharMap(){
    static char **map = NULL;
    if(map == NULL)

    {
        map= calloc(10,sizeof(char*));
        char *rows = calloc(10, sizeof(char));
        for (int i = 0; i<10; i++)
        {

            map[i] = calloc(rows[i], sizeof(char));

            for (int j = 0; j<rows[i]; j++)
            {
                map[i][j] = '0';
            }
        }

    }


    return map;
}

Map *getMapInstance(){
    static Map *gameMap = NULL;
    if(gameMap == NULL){
        gameMap = malloc(sizeof(Map));
        gameMap -> mapSizeY = 10;
        gameMap -> mapSizeX = 10;
        gameMap -> cells = calloc(gameMap -> mapSizeX, sizeof(Object**)); // 10 == X dimension

        for(int y = 0; y<gameMap -> mapSizeX; y++)
        {
            gameMap -> cells[y] = calloc(gameMap -> mapSizeY,sizeof(Object));
        }
    }

    return gameMap;
}

void initMapByObjects(){
    char **map = getCharMap();
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10;x++)
        {
            newCell(0,y,x);

            if(configMap[y][x]>0)
            {
                Object *tmp =  generateNewObject(configMap[y][x], y,x);
                addObjToCell(tmp,y,x);
            }
        }
    }
}

void printMaps()
{
    printConsoleMap();
    printGraphicMap();
}

void printConsoleMap(){
    system("clear");
    Map *map = getMapInstance();
    char **mapChar = getCharMap();

    for(int y = 0 ; y < map->mapSizeY;y++)
    {
        for (int x = 0; x < map->mapSizeX; x++)
        {
            //for visual better visual debug
            switch (getCell(y,x)->last->textureId)
            {
                case 0:
                printf(" %c",'.');
                mapChar[y][x] = '0';
                break;


                case 2:
                printf(" %c",'#');
                mapChar[y][x] = '2';
                break;

                case 3:
                printf(" %c",'@');
                mapChar[y][x] = '3';
                break;

                case 4:
                printf(" %c",'@');
                    mapChar[y][x] = '4';
                break;

                case 11:
                printf(" %c",'A');
                    mapChar[y][x] = '5';
                break;

                case 12:
                printf(" %c",'B');
                    mapChar[y][x] = '6';
                break;

                case 13:
                printf(" %c",'C');
                break;

                case 14:
                printf(" %c",'D');

                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                printf(" %c",'*');
                break;

                case 99:
                printf(" %c",'X');
                    mapChar[y][x] = '9';
                break;

                default:
                printf(" %d",getCell(y,x)->last->textureId);
                    mapChar[y][x] = '0';
                break;
            }

        }
        printf("\n");
    }
   // printGraphicMap();
}
