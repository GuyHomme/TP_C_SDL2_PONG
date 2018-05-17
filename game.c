#include "game.h"

//MEMORY
void FreeCursor(MouseInfos *mouse)
{
    if(mouse != NULL)
    {
        if(mouse->m_body != NULL)
            SDL_free(mouse->m_body);
        free(mouse);
    }
}

void FreePlayers(Player *players)
{
    if(players != NULL)
    {
        free(players);
    }
}

void FreeWidgets(Widget *widgets, int *nbWidgets)
{
    int i = 0;

    if(*nbWidgets > 0 && widgets != NULL)
    {
        for(i = 0 ; i < *nbWidgets ; i ++)
        {
            if(widgets[i].m_body != NULL)
                SDL_free(widgets[i].m_body);
        }
        *nbWidgets = 0;
        free(widgets);
    }
}

void FreeActors(Actor *actors, int *nbActors)
{
    int i = 0;

    if(*nbActors > 0 && actors != NULL)
    {
        for(i = 0 ; i < *nbActors ; i ++)
        {
            FreeActor(&actors[i]);
        }
        *nbActors = 0;
        free(actors);
    }
}

void Destroy(Game *myGame, int *nbActors, int *nbWidgets)
{
        if(myGame->g_pTexture!=NULL)
            SDL_DestroyTexture(myGame->g_pTexture);
        if(myGame->g_pRenderer!=NULL)
            SDL_DestroyRenderer(myGame->g_pRenderer);
        if(myGame->g_pWindow!=NULL)
            SDL_DestroyWindow(myGame->g_pWindow);
        FreeActors(myGame->g_Actors, nbActors);
        FreeWidgets(myGame->g_Widgets, nbWidgets);
        FreeCursor(myGame->g_mouseInfos);
}
    //INIT
int Init(char *title, int xpos, int ypos, int width, int height, int flags, Game *myGame)
{
    myGame->g_pRenderer = NULL;
    myGame->g_pTexture = NULL;
    myGame->g_pWindow = NULL;
    myGame->g_Actors = NULL;
    myGame->g_Widgets = NULL;
    myGame->g_Players = NULL;
    myGame->g_mouseInfos->m_body = NULL;

    if (!SDL_Init(SDL_INIT_EVERYTHING) >= MIN0)
    {
        myGame->g_pWindow = SDL_CreateWindow(title,xpos,ypos,width,height,flags);

        if(myGame->g_pWindow!=NULL)
        {
            myGame->g_pRenderer = SDL_CreateRenderer(myGame->g_pWindow, -MIN1, SDL_RENDERER_ACCELERATED);
            if(myGame->g_pRenderer != NULL)
            {
                myGame->g_pTexture = SDL_CreateTexture(myGame->g_pRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH,SCREEN_HEIGHT);

                if(myGame->g_pTexture != NULL)
                {
                    SDL_SetRenderDrawColor(myGame->g_pRenderer, RGBA_Black().m_R, RGBA_Black().m_G, RGBA_Black().m_B, RGBA_Black().m_A); //Black window
                    SDL_RenderPresent(myGame->g_pRenderer);
                    SDL_RenderClear(myGame->g_pRenderer);

                    myGame->g_State = Running;
                    myGame->g_Mode = None;

                    return EXIT_SUCCESS;
                }
            }
        }
    }
    return EXIT_FAILURE;
}

//RENDERING
void RenderingAll(Game *myGame, int nbActors, int nbWidgets)
{
    RenderingAllActors(myGame, nbActors);
    RenderingAllWidgets(myGame, nbWidgets);

    SDL_RenderPresent(myGame->g_pRenderer);
    SDL_RenderClear(myGame->g_pRenderer);
    SDL_SetRenderTarget(myGame->g_pRenderer, NULL);
    SDL_SetRenderDrawColor(myGame->g_pRenderer, RGBA_Black().m_R, RGBA_Black().m_G, RGBA_Black().m_B, RGBA_Black().m_A);
}

void RenderingAllWidgets(Game *myGame, int nbWidgets)
{
    int i = 0;

    for(i = 0 ; i < nbWidgets ; i++)
    {
        SDL_SetRenderDrawColor(myGame->g_pRenderer,
                               myGame->g_Widgets[i].m_color.m_R,
                               myGame->g_Widgets[i].m_color.m_G,
                               myGame->g_Widgets[i].m_color.m_B,
                               myGame->g_Widgets[i].m_color.m_A);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_pTexture);
        SDL_RenderFillRect(myGame->g_pRenderer, myGame->g_Widgets[i].m_body);
    }
    SDL_SetRenderTarget(myGame->g_pRenderer, NULL);
    SDL_SetRenderDrawColor(myGame->g_pRenderer, RGBA_Black().m_R, RGBA_Black().m_G, RGBA_Black().m_B, RGBA_Black().m_A);
}

void RenderingAllActors(Game *myGame, int nbActors)
{
    int i = 0;

    for(i = 0 ; i < nbActors ; i++)
    {
        SDL_SetRenderDrawColor(myGame->g_pRenderer,
                               myGame->g_Actors[i].m_color.m_R,
                               myGame->g_Actors[i].m_color.m_G,
                               myGame->g_Actors[i].m_color.m_B,
                               myGame->g_Actors[i].m_color.m_A);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_pTexture);
        SDL_RenderFillRect(myGame->g_pRenderer, myGame->g_Actors[i].m_body);
    }
    SDL_SetRenderTarget(myGame->g_pRenderer, NULL);
    SDL_SetRenderDrawColor(myGame->g_pRenderer, RGBA_Black().m_R, RGBA_Black().m_G, RGBA_Black().m_B, RGBA_Black().m_A);
}

//MENUS HANDLER
int EnterMainMenu(Game *myGame, int nbWidgets)
{
    int i = 0;

    SDL_ShowCursor(1);

    myGame->g_mouseInfos = (MouseInfos*)calloc(1, sizeof(MouseInfos));
    myGame->g_Widgets = (Widget*)calloc(nbWidgets, sizeof(Widget));

    if(myGame->g_mouseInfos != NULL && myGame->g_Widgets != NULL)
    {
        myGame->g_mouseInfos->m_body = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));

        if(myGame->g_mouseInfos->m_body != NULL)
        {
            SetRectSizeRough(myGame->g_mouseInfos->m_body, 2, 2); // Setting the size of the cursor

            for(i = 0 ; i < nbWidgets ; i ++)
            {
                myGame->g_Widgets[i].m_body = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
                if(myGame->g_Widgets[i].m_body == NULL)
                    return EXIT_FAILURE;
            }
            myGame->g_Mode = Menu;

            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int EnterPlayMode(Game *myGame, int nbActors, int boolSolo)
{
    int i = 0;
    myGame->g_Actors = (Actor*)calloc(nbActors, sizeof(Actor));
    myGame->g_Players = (Player*)calloc(NB_PLAYERS, sizeof(Player));

    SDL_ShowCursor(0);
    if(myGame->g_Actors != NULL && myGame->g_Players != NULL)
    {
        for(i = 0 ; i < nbActors ; i++)
        {
            myGame->g_Actors[i].m_body = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));

            if(myGame->g_Actors[i].m_body == NULL)
                return EXIT_FAILURE;
        }
        myGame->g_Mode = (boolSolo) ? Solo : Multi;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int LeaveGame(Game *myGame)
{
    myGame->g_Mode = None;
    myGame->g_State = Closed;

    return EXIT_SUCCESS;
}

//UTILITIES
void Delay(unsigned int frameLimit)
{
        unsigned int ticks = SDL_GetTicks();

        if (frameLimit < ticks)
                return;

        if (frameLimit > ticks + MAXIMAGEPS)
                SDL_Delay(MAXIMAGEPS);
        else
                SDL_Delay(frameLimit - ticks);
}

InEvent HandleEvents(Game *myGame)
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return force_quit;
            case SDL_MOUSEBUTTONDOWN:
                MoveRectToCoords(myGame->g_mouseInfos->m_body, event.button.x, event.button.y); //Moving the coordinates of the cursor body to the event coordinates
                return mouse_click;
            case SDL_KEYDOWN:
                switch(myGame->g_Mode)
                {
                case Solo:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                                return key_esc;
                        case SDLK_s:
                                return key_s;
                        case SDLK_z:
                                return key_z;
                        default:
                            return no_event;
                    }
                    break;
                case Multi: //For the multi mode, we also want to handle the Z-S axis inputs for the second player
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                                return key_esc;
                        case SDLK_UP:
                                return key_up;
                        case SDLK_DOWN:
                                return key_down;
                        case SDLK_s:
                                return key_s;
                        case SDLK_z:
                                return key_z;
                        default:
                            return no_event;
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
    }
        return no_event;
}

Widget* TryFocusOnWidget(Game *myGame, int nbWidgets)
{
    int i = 0;

    if(nbWidgets > 0 && myGame->g_Widgets != NULL)
    {
        for(i = 0 ; i < nbWidgets ; i ++)
        {
            if(SDL_HasIntersection(myGame->g_Widgets[i].m_body, myGame->g_mouseInfos->m_body))
            {
                return &myGame->g_Widgets[i];
            }
        }
    }
    return NULL;
}
