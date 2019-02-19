#include "bomberman.h"

bomber* game_init()
{
    bomber * game = NULL;
    game = malloc(sizeof(bomber));
    game->choiceGame = NULL;
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pWindowMenu = NULL;
    game->pWindowMenuJoin = NULL;
    game->pRendererMenuJoin = NULL;
    game->pRendererMenu = NULL;
    game->pRenderer = NULL;
    // game->player1Position.x = 200;
    // game->player1Position.y = 150;
    game->player1Position.w = 40;
    game->player1Position.h = 40;
    game->ifBombe = 0;
    game->start = 0;
    game->bombe = NULL;


    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError());
        game_destroy(game);
        return (NULL);
    }
    return(game);
}
void create_game(bomber* game)
{
    //Creation jeu si menu okey
        game->pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
        if (game->pWindow) {
            //Crea renderer
            game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
            if (!game->pRenderer) {
                fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
                game_destroy(game);
                exit(1);
            }
        } else {
            fprintf(stderr, "Impossible de créer le fenetre SDL : %s\n", SDL_GetError());
            game_destroy(game);
           exit(1);
        }

        SDL_Surface* surfaceBomby = IMG_Load("bombe.png");
        if (!surfaceBomby) {
            fprintf(stderr, "Impossible de charger l'image bombe.png : %s\n", IMG_GetError());
            game_destroy(game);
            exit(1);
        } else { 
            game->pTexturePlayer = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBomby);
            if (!game->pTexturePlayer) {
                fprintf(stderr, "Impossible de charger  la texture : %s\n", SDL_GetError());
                game_destroy(game);
                exit(1);
            }
            SDL_FreeSurface(surfaceBomby);
        }



        //Chargement texture map + perso 
        game->img_texture[1] = IMG_Load("tileset_bomberman.bmp");
        game->img_texture[2] = IMG_Load("perso.bmp");
        if (!game->img_texture[1]) {
            fprintf(stderr, "Impossible de charger l'image 10 : %s\n", IMG_GetError());
            game_destroy(game);
            exit(1);
        } else if (!game->img_texture[2]) {
            fprintf(stderr, "Impossible de charger l'image 11 : %s\n", IMG_GetError());
            game_destroy(game);
            exit(1);
        }
}

void game_destroy(bomber* game)
{

    int x;
    int y;

    if (game) {
        if(game->ClientJoinGame){
            SDL_DestroyTexture(game->ClientJoinGame);
        }
        if(game->texture_text){
            SDL_DestroyTexture(game->texture_text);
        }

        if(game->pTextureMenu) {
            SDL_DestroyTexture(game->pTextureMenu);
        }

        if (game->pTexturePlayer) {
            SDL_DestroyTexture(game->pTexturePlayer);
        }

        for (y = 0; y < NOMBRE_BLOCS_LARGEUR; y++) {
            for (x = 0; x < NOMBRE_BLOCS_HAUTEUR; x++) {
                if (game->textures[y][x]) {
                    SDL_DestroyTexture(game->textures[y][x]);
                }
            }
        }
        if (game->pRendererMenuJoin) {
            SDL_DestroyRenderer(game->pRendererMenuJoin);
        }
        if (game->pRendererMenu) {
            SDL_DestroyRenderer(game->pRendererMenu);
        }
        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer);
        }
        if (game->pWindowMenuJoin) {
            SDL_DestroyWindow(game->pWindowMenuJoin);
        }
        if (game->pWindowMenu) {
            SDL_DestroyWindow(game->pWindowMenu);
        }
        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}

void game_show(bomber* game, char* direction)
{
    int y;
    int x;
    SDL_Rect Rect_dest;
    SDL_Rect Src_dest;
    //clean l'ecran
    SDL_SetRenderDrawColor(game->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(game->pRendererMenuJoin);
    SDL_RenderClear(game->pRendererMenu);
    SDL_RenderClear(game->pRenderer);
    //menu 
    if(game->menuOn == 1) {
        SDL_RenderCopy(game->pRendererMenu, game->pTextureMenu, NULL, &game->Menu);
        SDL_RenderCopy(game->pRendererMenu, game->texture_text, NULL, &game->startTxt);
        SDL_RenderCopy(game->pRendererMenu, game->ClientJoinGame, NULL, &game->joingame);
        SDL_RenderCopy(game->pRendererMenu, game->ClientHostGame, NULL, &game->hostGame);
        SDL_RenderCopy(game->pRendererMenu, game->cursor, NULL, &game->cursorBomb);
        SDL_RenderPresent(game->pRendererMenu); 
    } else if (game->menuOn == 0) {
        SDL_RenderCopy(game->pRendererMenuJoin, game->pTextureMenuJoin, NULL, &game->Menu);
        SDL_RenderCopy(game->pRendererMenuJoin, game->txtJoin, NULL, &game->startTxt);
        SDL_RenderCopy(game->pRendererMenuJoin, game->textIp, NULL, &game->joingame);
        SDL_RenderPresent(game->pRendererMenuJoin);
        if(game->start == 1){
            //Afficher la map + joueur
            for(y=0; y < NOMBRE_BLOCS_LARGEUR; y++) {
                for(x=0; x < NOMBRE_BLOCS_HAUTEUR; x++) {
                    Src_dest = get_src_dest(game->map[y][x], direction); // cas qui gère l'image à afficher
                    Rect_dest.x = x * 50;
                    Rect_dest.y = y * 50;
                    Rect_dest.w = 50;
                    Rect_dest.h = 50;
                    SDL_RenderCopy(game->pRenderer, game->textures[y][x], &Src_dest, &Rect_dest);
                }
            }

            //afficher la bombe
            if(game->ifBombe == 1) {
                //printf( "%d\n", game->bombe->position.x);
                SDL_RenderCopy(game->pRenderer, game->pTexturePlayer, NULL, &game->bombe->position);
            }   

            //Afficher rendu
            SDL_RenderPresent(game->pRenderer);
        }
    }
}

int game_event(bomber* game)
{
    int result = 0;
    SDL_Event e;
    SDL_Delay(200);
    game_show(game, "null");
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            //quitte le jeu
            result = -1;
        } else if (e.type == SDL_KEYDOWN) {
            //gerer touche du clavier
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE :
                result = -1;
                break;               
            case SDLK_UP:
                if(game->start == 1) {
                    game_movePlayer(game, e.key.keysym.sym);
                    game_show(game, "up");
                } else {
                    menuScroll("up", game);
                }
                break;
            case SDLK_DOWN:
                if(game->start == 1) {
                    game_movePlayer(game, e.key.keysym.sym);
                    game_show(game, "down");
                } else{
                    menuScroll("down", game);
                }
                
                break;
            case SDLK_LEFT:
                if(game->start == 1) {
                    game_movePlayer(game, e.key.keysym.sym);
                    game_show(game, "left");
                }
                break;
            case SDLK_RIGHT:
                if(game->start == 0) {
                    game_movePlayer(game, e.key.keysym.sym);
                    game_show(game, "right");
                }
                break;
            case SDLK_d:
            if (game->start == 1) {
                game_dropBombe(game);
                game_show(game, "null");
            }
                break;
            case SDLK_RETURN:
                SDL_HideWindow(game->pWindowMenu);
                if(game->cursorBomb.y == game->joingame.y) {
                    init_menuJoin(game);
                    game->choiceGame = "join";
                    SDL_ShowWindow(game->pWindowMenuJoin);
                    game->menuOn = 0;
                }
               // create_game(game);
                //init_map(game);
               // SDL_ShowWindow(game->pWindow);
                //game->menuOn = 0;
                break;
            default:
                fprintf(stderr, "touche inconnue %d\n", e.key.keysym.sym);
                break;
            }
        }
    }
    return (result);
}
