#include "bomberman.h"

void init_menuJoin(bomber* game)
{
//création menu pour rejoindre 
    game->pWindowMenuJoin = SDL_CreateWindow("Join a game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    if(game->pWindowMenuJoin){
        game->pRendererMenuJoin = SDL_CreateRenderer(game->pWindowMenuJoin, -1, SDL_RENDERER_ACCELERATED);
        if(!game->pRendererMenuJoin) {
            fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            exit(1);
        }
        create_menu_join(game);
    } else {
        fprintf(stderr, "Impossible de créer le fenetre SDL : %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }  
}

void create_menu_join(bomber* game)
{
    game->pTextureMenuJoin = NULL;
    game->textIp = NULL;
    game->txtJoin = NULL;
    game->userIp = NULL;
    int font_size = 24;
    char * text = "Join a game";
    char * textIP = "Ip address : ";
    // char *server_ip = NULL;

// *****
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
                    strcpy(str, "exit");
                    boucle = false;
                    break ;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            strcpy(str, "exit");
                            boucle = false;
                            break ;
                        case SDLK_RETURN:
                            if (str_size > 0)
                                boucle = false;
                            break ;
                        case SDLK_BACKSPACE:
                            if (str_size)
                            {
                                str[str_size - 1] = '\0';
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

        SDL_RenderClear(game->pRendererMenuJoin);

// ****

    SDL_Color normalColor = {255, 255, 255, 255};
    SDL_Surface* surface_background;
    SDL_Surface* surface_text;
    SDL_Surface* surface_textIp;
    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);


    surface_background = SDL_LoadBMP("assets/img/main_menu.bmp");
    if ( !surface_background ){
        fprintf(stdout,"Échec de chargement du background (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_text = TTF_RenderText_Solid(police, text, normalColor);
    if ( !surface_text ){
        fprintf(stdout,"Échec de chargement du text (%s)\n",SDL_GetError());
        game_destroy(game);
    }

    surface_textIp = TTF_RenderText_Solid(police, textIP, normalColor);
    if ( !surface_textIp ) {
        fprintf(stdout,"Échec de chargement du textIP (%s)\n",SDL_GetError());
        game_destroy(game);
    }
    TTF_CloseFont(police);
    
    game->pTextureMenuJoin = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_background);
    if ( !game->pTextureMenuJoin ){
        fprintf(stdout,"Échec de création de la textureMenuJoin - %s\n",SDL_GetError());
        game_destroy(game);
    }
    SDL_FreeSurface(surface_background);

    game->txtJoin = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_text);
    if (!game->txtJoin) {
        fprintf(stderr, "Impossible de charger  la texture txtJoin: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }

    game->textIp = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface_textIp);
    if (!game->textIp) {
        fprintf(stderr, "Impossible de charger  la texture textIp: %s\n", SDL_GetError());
        game_destroy(game);
        exit(1);
    }
    SDL_FreeSurface(surface_textIp);

//***
        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - 40, "Adresse ip :", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());
        if (str_size)
            draw_text(str, game);

        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT - 50), "Echap pour quitter", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());

        SDL_RenderPresent(game->pRendererMenuJoin);

        init = true;
    }

    SDL_StopTextInput();


//***

}

void draw_text(char *text, bomber* game)
{
    int font_size = 24;
    int textureWidth;
    int textureHeigth;
    SDL_Color normalColor = {255, 0, 0, 1};

    TTF_Font* police = TTF_OpenFont("./arial.ttf", font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(police, text, normalColor);
    if (!surface){
        printf("Une erreur est survenue lors de l'ajout de surface : '%s'\n", SDL_GetError());
        return ;
    }

    TTF_CloseFont(police);

    // On transforme la surface en texture pour l'afficher avec le renderer
    game->userIp = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface);
    if (!game->userIp) {
        printf("Une erreur est survenue lors du chargement de la texture userIp : '%s'\n", SDL_GetError());
        return ;
    }
    // On free la surface
    SDL_FreeSurface(surface);

    // On récupère la longueur et hauteur de la texture
    SDL_QueryTexture(game->userIp, NULL, NULL, &textureWidth, &textureHeigth);

    // On crée un rect qui va correspondre à la position du texte
    game->userTextIpJoin.x = 200;
    game->userTextIpJoin.y = 110;
    game->userTextIpJoin.w = textureWidth;
    game->userTextIpJoin.h = textureHeigth;
}
