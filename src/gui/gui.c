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

    SDL_Surface *playerImg = IMG_Load("./images/playerTileset.bmp");
    SDL_Surface *gameImg = IMG_Load("./images/gameTileset.bmp");

    if(!playerImg || !gameImg)
    {
        fprintf(stderr, "Fail of load *tillset.bmp : %s\n", SDL_GetError());
        gameDestroy();
    }

    game->playerTileset = SDL_CreateTextureFromSurface(game->renderer,playerImg);
    game->gameTileset = SDL_CreateTextureFromSurface(game->renderer,gameImg);
    return game;
}

void printGraphicMap(char *map)
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
        for(int x=0;x<lengthX;x++)
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
}

SDL_Texture * getTextureByCharValue(char value) {

    Game *game = getGame();
    SDL_Texture *texture = NULL;
    switch (value)
    {
        case '.'://CELL
        case 'X'://BLOCK
        case '#'://WALL
        case '@'://BOOMB
        case '*'://EXPLOSION
            texture = game->gameTileset;
        break;

        case 'A':
        case 'B':
        case 'C':
        case 'D': //PLAYER
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
    switch (value)
    {
        case '.'://CELL
            result.x = 3 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;

            break;

        case 'X'://BLOCK
            result.x = 1 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case '#'://WALL

            result.x = 2 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;

        case '@'://BOOMB

            result.x = 7 * CELL_TILE_SIZE;
            result.y = 6 * CELL_TILE_SIZE;
            break;

        case 'A':
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 0 * CELL_TILE_SIZE;
            break;
        case 'B':
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 1 * CELL_TILE_SIZE;
            break;
        case 'C':
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 2 * CELL_TILE_SIZE;
            break;
        case 'D': //PLAYER
            result.x = 0 * CELL_TILE_SIZE;
            result.y = 3 * CELL_TILE_SIZE;
            break;


        case '*'://EXPLOSION
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

    if(getGame()->gameTileset)
        SDL_DestroyTexture(getGame()->gameTileset);
    if(getGame()->playerTileset)
        SDL_DestroyTexture(getGame()->playerTileset);
    if(getGame()->renderer)
        SDL_DestroyRenderer(getGame()->renderer);
    if(getGame()->window)
        SDL_DestroyWindow(getGame()->window);
    SDL_Quit();
}

char getPressedKey(){
    SDL_Event e;
    char key = 10;
    if ( SDL_PollEvent(&e) )
    {



    if (e.type == SDL_QUIT)
        exit(1);
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

    }
    if(key!=10)
        printf("key %c \n",key);
    return key;
}
