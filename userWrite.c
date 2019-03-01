#include "bomberman.h"

char* userWrite(bomber* game)
{
    char    *str;
    if ((str = malloc(32 * sizeof(char))) == NULL)
        exit(0);
    strcpy(str, "");
    SDL_StartTextInput();
    int str_size = 0;
    bool init = false;
    SDL_Event e;
    bool boucle = true;
    while(boucle)
    {
        if (init)
        {
            SDL_WaitEvent(&e);
            switch(e.type)
            {
                case SDL_QUIT:
                   // strcpy(str, "exit");
                    boucle = false;
                    break ;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                       /* case SDLK_ESCAPE:
                            strcpy(str, "exit");
                            boucle = false;
                            break ;*/
                        case SDLK_RETURN:
                            if (str_size > 0)
                                boucle = false;
                            break ;
                        case SDLK_BACKSPACE:
                            if(str_size) {
                                str[str_size - 1 ] = '\0';
                                str_size--;
                            }

                            break ;
                    }
                    break ;
                case SDL_TEXTINPUT:
                    if (str)
                    {
                        if (str_size < 31)
                        {
                            strcat(str, e.text.text);
                            str_size += 1;
                        }
                    }
                    break ;
            }
        }
        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - 40, "Adresse ip :", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());
        if (str_size) 
            draw_text(str, game);
        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT - 50), "Echap pour quitter", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());
        game_show(game, "null");
        init = true;
    }

    SDL_StopTextInput();
    return(str);
}
void draw_text(char *text, bomber* game)
{
    int font_size = 24;
    int textureWidth;
    int textureHeigth;
    int textureWidthP;
    int textureHeigthP;
    SDL_Color normalColor = {255, 0, 0, 1};

    TTF_Font* police = TTF_OpenFont("../assets/arial.ttf", font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(police, text, normalColor);
    if (!surface){
        printf("Une erreur est survenue lors de l'ajout de surface : '%s'\n", SDL_GetError());
        return ;
    }

    TTF_CloseFont(police);

    // On transforme la surface en texture pour l'afficher avec le renderer
    if((strcmp(game->ipIsOk, "") == 0 || strcmp(game->ipIsOk, "no") == 0) && game->cursorBomb.y == game->joingame.y) {
        game->userText = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface);
        if (!game->userText) {
            printf("Une erreur est survenue lors du chargement de la texture userIp : '%s'\n", SDL_GetError());
            return ;
        }
    } else {
        if(game->cursorBomb.y == game->joingame.y) 
            game->userTextPort = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface);
        else {
            game->userTextPort = SDL_CreateTextureFromSurface(game->pRendererMenuHost, surface);
        }
        if (!game->userTextPort) {
            printf("Une erreur est survenue lors du chargement de la texture user Port : '%s'\n", SDL_GetError());
            return ;
        } 
    }
    // On free la surface
    SDL_FreeSurface(surface);

    // On récupère la longueur et hauteur de la texture
    SDL_QueryTexture(game->userText, NULL, NULL, &textureWidth, &textureHeigth);
    SDL_QueryTexture(game->userTextPort, NULL, NULL, &textureWidthP, &textureHeigthP);

    // On crée un rect qui va correspondre à la position du texte pour le menu rejoindre
    if (strcmp(game->ipIsOk, "") == 0 || strcmp(game->ipIsOk, "no") == 0) {
        game->userTextIpJoin.x = 200;
        game->userTextIpJoin.y = 115;
        game->userTextIpJoin.w = textureWidth;
        game->userTextIpJoin.h = textureHeigth;
    }
    if(strcmp(game->ipIsOk, "ok")== 0) {
        game->userTextPortJoin.x = 200;
        game->userTextPortJoin.y = 185;
        game->userTextPortJoin.w = textureWidthP;
        game->userTextPortJoin.h = textureHeigthP;
    }

    //dans le cas du host (oui j'ai pris le même sdlRect que join)
    if(game->cursorBomb.y == game->hostGame.y) {
        game->userTextIpJoin.x = 200;
        game->userTextIpJoin.y = 115;
        game->userTextIpJoin.w = textureWidthP;
        game->userTextIpJoin.h = textureHeigthP;
    }
}

