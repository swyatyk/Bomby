#include "bomberman.h"

void draw_text(char *text, bomber* game)
{
    int font_size = 20;
    SDL_Color normalColor = {255, 0, 0, 1};


    TTF_Font* police = TTF_OpenFont("./assets/arial.ttf", font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(police, text, normalColor);
    if (!surface)
    {
        printf("Une erreur est survenue lors du rendering de texte : '%s'\n", SDL_GetError());
        return ;
    }


    // On transforme la surface en texture pour l'afficher avec le renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->pRendererMenuJoin, surface);
    if (!texture)
    {
        printf("Une erreur est survenue lors du rendering de texte : '%s'\n", SDL_GetError());
        return ;
    }

    // On free la surface
    SDL_FreeSurface(surface);


    int textureWidth, textureHeight;

    // On récupère la longueur et hauteur de la texture
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // On crée un rect qui va correspondre à la position du texte
    SDL_Rect rect = {100, 250, textureWidth, textureHeight};


    // on render la texture via le renderer
    SDL_RenderCopy(game->pRendererMenuJoin, texture, NULL, &rect);

    // on destroy la texture
    SDL_DestroyTexture(texture);
}

char        *choose_server(bomber* game)
{
    char    *str;

    if ((str = malloc(32 * sizeof(char))) == NULL)
        return (NULL);

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

        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - 40, "Adresse ip :", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());
        if (str_size)
            draw_text(str, game);

        // draw_text((WINDOW_WIDTH / 2), (WINDOW_HEIGHT - 50), "Echap pour quitter", TEXT_CENTER, get_default_font(), COLOR_WHITE, get_game_renderer());

        SDL_RenderPresent(game->pRendererMenuJoin);

        init = true;
    }

    SDL_StopTextInput();

    return (str);
}