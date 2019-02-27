//
// Created by Sviatoslav Prylutsky on 2/5/19.
//

#include "headers/gui.h"
#include "../instances/headers/player.h"
#include "../instances/headers/map.h"
#include "../instances/headers/cell.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WIDHT_TILE 100
#define HEIGHT_TILE 100
#define CELL_TILE_SIZE 100
#define WIDTH_CELL_CNT = 10
#define HEIGHT_CELL_CNT = 10

void gameDestroy();

SDL_Rect getRectByTextureId(int typeId);

Game * getGame()
{
    static Game *game = NULL;
    if(game==NULL){
        game = malloc(sizeof(Game));

    }
    return game;
}


Game * gameInit()
{

    Game *game = getGame();

    if(SDL_Init(SDL_INIT_VIDEO>0)){printf("SDL Start failed;");gameDestroy();}

    game->window = SDL_CreateWindow("Bomberman",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(!game->window){
        fprintf(stderr, "Init window Fail SDL : %s\n", SDL_GetError());
        gameDestroy();
    }

    game->renderer = SDL_CreateRenderer(game->window,-1,SDL_RENDERER_ACCELERATED);
    if(!game->renderer){
        fprintf(stderr, "Init render fail SDL : %s\n", SDL_GetError());
        gameDestroy();
    }

    SDL_Surface *playerImg = IMG_Load("../images/playerTileset.bmp");
    SDL_Surface *gameImg = IMG_Load("../images/gameTileset.bmp");

    if(!playerImg || !gameImg)
    {
        fprintf(stderr, "Fail of load *tillset.bmp : %s\n", SDL_GetError());
        gameDestroy();
    }

    game->playerTileset = SDL_CreateTextureFromSurface(game->renderer,playerImg);
    game->gameTileset = SDL_CreateTextureFromSurface(game->renderer,gameImg);
}

void printGraphicMap()
{

    Game *game = getGame();
    SDL_RenderClear(game->renderer);

    int lengthX = 10;
    int lengthY = 10;
    int cell_tile_height = 48;
    int cell_tile_width = 64;

    SDL_Rect r_dest,r_src;
    // int (*map)[10][10] = getMapInstance();
    for(int x=0;x<lengthX;x++)
    {
        for(int y=0;y<lengthY;y++)
        {
            r_src = getRectByTextureId(getCell(y,x)->last->textureId);
            r_dest.x = x*cell_tile_width;
            r_dest.y = y*cell_tile_height;
            r_dest.w = cell_tile_width;
            r_dest.h = cell_tile_height;
            if(getCell(y,x)->last->textureId>10 && getCell(y,x)->last->textureId<15)
            {
                SDL_RenderCopy(game->renderer, game->playerTileset, &r_src, &r_dest);
            }
            else
            {
                SDL_RenderCopy(game->renderer, game->gameTileset, &r_src, &r_dest);
            }

        }

    }
    SDL_RenderPresent(game->renderer);
  /* SDL_Delay(1000);
    SDL_DestroyTexture(game->playerTileset);*/
}

void printGraphicMapFromSever(char *map)
{

    Game *game = getGame();
    SDL_RenderClear(game->renderer);

    int lengthX = 10;
    int lengthY = 10;
    int cell_tile_height = 48;
    int cell_tile_width = 64;

    SDL_Rect r_dest,r_src;
    for(int y=0;y<lengthY;y++)
    {
        for(int x=0;x<lengthY;x++)
        {
            char value = map[y + 10 * x];
            r_src = getRectByCharValue(value);
            r_dest.x = x*cell_tile_width;
            r_dest.y = y*cell_tile_height;
            r_dest.w = cell_tile_width;
            r_dest.h = cell_tile_height;
            SDL_RenderCopy(game->renderer, getTextureByCharValue(value), &r_src, &r_dest);

        }

    }
    SDL_RenderPresent(game->renderer);
  /* SDL_Delay(1000);
    SDL_DestroyTexture(game->playerTileset);*/
}

SDL_Texture * getTextureByCharValue(char value) {

    Game *game = getGame();
    SDL_Texture *texture = NULL;
    switch (value)
    {
        case '0'://CELL
        case '1'://BLOCK
        case '2'://WALL
        case '3': //BOOMB
        case '20':
        case '21':
        case '22':
        case '23':
        case '24':
            texture = game->gameTileset;
        break;

        case '11':
        case '12':
        case '13':
        case '14': //PLAYER
            texture = game->playerTileset;
        break;

        default://OBJECT
            texture = game->gameTileset;
         break;
    }


    return texture;
}
SDL_Rect getRectByCharValue(char value) {
    SDL_Rect result;
    Game *game = getGame();
    switch (value)
    {
        case '0'://CELL
            result.x = 3 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;

            break;

        case '1'://BLOCK
            result.x = 1 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case '2'://WALL

            result.x = 2 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case '3': //BOOMB

            result.x = 7 * CELL_TILE_SIZE;
            result.y = 6 * CELL_TILE_SIZE;
            break;

        case '11':
        case '12':
        case '13':
        case '14': //PLAYER
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;


        case '20':
        case '21':
        case '22':
        case '23':
        case '24':
            //EXPLOSION
            result.x = 4 * CELL_TILE_SIZE;
            result.y = 3 * CELL_TILE_SIZE;
            break;

        default://OBJECT
            result.x = 8 * CELL_TILE_SIZE;
            result.y = 8 * CELL_TILE_SIZE;
            break;
    }

    result.w = CELL_TILE_SIZE;
    result.h = CELL_TILE_SIZE;

    return result;
}


SDL_Rect getRectByTextureId(int typeId) {
    SDL_Rect result;

    switch (typeId)
    {
        case 0://CELL
            result.x = 3 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;

            break;

        case 99://BLOCK
            result.x = 1 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case 2://WALL

            result.x = 2 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case 3: //BOOMB

            result.x = 7 * CELL_TILE_SIZE;
            result.y = 6 * CELL_TILE_SIZE;
            break;

        case 11:
        case 12:
        case 13:
        case 14: //PLAYER
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;


        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            //EXPLOSION
            result.x = 4 * CELL_TILE_SIZE;
            result.y = 3 * CELL_TILE_SIZE;
            break;

        default://OBJECT
            result.x = 8 * CELL_TILE_SIZE;
            result.y = 8 * CELL_TILE_SIZE;
            break;
    }

    result.w = CELL_TILE_SIZE;
    result.h = CELL_TILE_SIZE;

    return result;
}


void gameDestroy() {

    SDL_DestroyTexture(getGame()->playerTileset);
    SDL_DestroyRenderer(getGame()->renderer);
    SDL_DestroyWindow(getGame()->window);
    SDL_Quit();
}

char getPressedKey(){
    SDL_Event e;
    char key = 10;
    if (SDL_PollEvent(&e) && e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case 27 :
                key = 'p';
                break;

            case SDLK_w:
                key = 'w';
                break;
            case SDLK_s:
                key =  's';
                break;
            case SDLK_a:
                key =  'a';
                break;
            case SDLK_d:
                key = 'd';
                break;
            case SDLK_b:
                key = 'b';
                break;
            default:
                fprintf(stderr, "Unkown key %d\n", e.key.keysym.sym);
                break;
        }
    }
    if(key!=10)
        printf("key %c \n",key);

    return key;
}
int keyreader(Object *player)
{
    SDL_Event e;
    if (SDL_PollEvent(&e) && e.type == SDL_KEYDOWN)
    {

       // printf("SLD KEY =%d \n", e.key.keysym.sym);

        switch (e.key.keysym.sym)
        {
            case 27 :
                return EXIT_SUCCESS;
                break;

            case SDLK_w:
                playerInterfaceController(player, 'w');
                break;
            case SDLK_s:
                playerInterfaceController(player, 's');
                break;
            case SDLK_a:
                playerInterfaceController(player, 'a');
                break;
            case SDLK_d:
                playerInterfaceController(player, 'd');
                break;
            case SDLK_b:
                playerInterfaceController(player, 'b');
                break;
            default:
                fprintf(stderr, "Unkown key %d\n", e.key.keysym.sym);
                break;
        }
    }
    return 1;
}