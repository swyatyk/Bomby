//
// Created by Sviatoslav Prylutsky on 2/5/19.
//



#include "headers/map.h"
#include "../gui/headers/gui.h"
#include "headers/cell.h"
#include "../network/headers/server.h"

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


/*
char **getCharMap(){
    static char **map =NULL;
    if(map==NULL)
    {
        map = (char**)calloc(10, sizeof(char**));
        for(int y = 0; y < 10; y++) {
            map[y] = calloc(10, sizeof(char*));
            for (int x = 0; x < 10; x++)
            {
                map[y][x]='0';
            }
        }
    }
    return map;
}

void setCellInCharMap(int y , int x, char ch){
    char **arr = getCharMap();
    arr[y][x] = ch;
}
*/

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
   // printConsoleMap();
   // remapMap();
   // notificateAllClients();
}

void printConsoleMap(){
    system("clear");
    Map *map = getMapInstance();

    for(int y = 0 ; y < map->mapSizeY;y++)
    {
        for (int x = 0; x < map->mapSizeX; x++)
        {
            //for visual better visual debug
            switch (getCell(y,x)->last->textureId)
            {
                case 0:
                printf(" %c",'.');
                break;

                case 2:
                printf(" %c",'#');
                break;

                case 3:
                printf(" %c",'@');
                break;

                case 4:
                printf(" %c",'@');
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
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                printf(" %c",'*');
                break;

                case 99:
                printf(" %c",'X');
                break;

                default:
                printf(" %d",getCell(y,x)->last->textureId);
                break;
            }

        }
        printf("\n");
    }
}


char getCharFromInt(int intValue){

    char charValue = 'z'; //z undefined
    switch (intValue)
    {
        case 0:
            charValue = '.';
            break;

        case 2:
            charValue = '#';
            break;

        case 3:
            charValue = '@';
            break;

        case 4:
            charValue = 'z';
            break;

        case 11:
            charValue = 'A';
            break;

        case 12:
            charValue = 'B';
            break;

        case 13:
            charValue = 'C';
            break;

        case 14:
            charValue = 'D';
            break;

        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            charValue = '*';
            break;

        case 99:
            charValue = 'X';
            break;

        default:
            charValue = 'z';
            break;

    }
    return charValue;
}

