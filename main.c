#include "define.h"

int main(int argc, char *argv[])
{
    //Initialization
    Game myGame;
    unsigned int frameLimit;
    int nbActors = NB_MIN_ACTORS, nbWidgets = NB_MIN_MENU_WIDGETS;
    int appState = 0;
    Widget *currentWidget = NULL;

    if (!Init("Pong game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &myGame))
    {
        printf("SDL successfully initialized.\n");
        if(!EnterMainMenu(&myGame, nbWidgets))
        {
            printf("Main menu successfully entered.\n");

            appState = EXIT_SUCCESS;
            nbActors = 0; //No actor in the main menu, only widgets

            InitMainMenu(myGame.g_Widgets);
            RenderingAll(&myGame, nbActors, nbWidgets);
            while(myGame.g_State == Running)
            {
                switch(myGame.g_Mode) //Handling each game mode
                {
                    case Menu:
                        switch(HandleEvents(&myGame)) //Testing the value returned by the game.h function 'HandleEvents'
                        {
                            case mouse_click:
                                if((currentWidget = TryFocusOnWidget(&myGame, nbWidgets)) != NULL) //If a widget is clicked, currentWidget is assigned to his address
                                {
                                    switch(currentWidget->m_id) //Testing the ID of the clicked widget
                                    {
                                    case WID_INDEX_PLAY_SOLO:   //In case of SOLO & MULTI PLAY BUTTON
                                    case WID_INDEX_PLAY_MULTI:
                                        printf("Clicked on play %s button\n", (currentWidget->m_id == WID_INDEX_PLAY_SOLO) ? "solo" : "multi");
                                        nbActors = NB_MIN_ACTORS;
                                        EnterPlayMode(&myGame, nbActors, currentWidget->m_id == WID_INDEX_PLAY_SOLO);
                                        //The only difference is the boolean passed as argument of the 'EnterPlayMode' function (Is it solo or multi mode ?)
                                        FreeWidgets(myGame.g_Widgets, &nbWidgets);
                                        InitMainActors(myGame.g_Actors);
                                        break;
                                    case WID_INDEX_LEAVE:   //In case of LEAVE
                                        printf("Clicked on leave button\n");
                                        LeaveGame(&myGame);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case Solo: //Handling solo play mode
                        switch(HandleEvents(&myGame))
                        {
                            case key_z:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], up);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE1], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE1].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_s:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], down);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE1], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE1].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_esc:
                                nbWidgets = NB_MIN_MENU_WIDGETS;
                                EnterMainMenu(&myGame, nbWidgets);
                                FreeActors(myGame.g_Actors, &nbActors);
                                FreePlayers(myGame.g_Players);
                                InitMainMenu(myGame.g_Widgets);
                                break;
                            default:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], none);
                                break;
                        }
                        BallMovement(&myGame, nbActors);
                        AiFollowBall(&myGame, nbActors);
                        break;
                    case Multi: //Handling multiplayer play mode
                        switch(HandleEvents(&myGame))
                        {
                            case key_z:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], up);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE1], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE1].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_s:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], down);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE1], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE1].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_down:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE2], down);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE2], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE2].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_up:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE2], up);
                                ActorMovement(&myGame.g_Actors[ACT_INDEX_PADDLE2], myGame.g_Actors, nbActors, myGame.g_Actors[ACT_INDEX_PADDLE2].m_speed, RawPointConstruct(0, 0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));
                                break;
                            case key_esc:
                                nbWidgets = NB_MIN_MENU_WIDGETS;
                                EnterMainMenu(&myGame, nbWidgets);
                                FreeActors(myGame.g_Actors, &nbActors);
                                FreePlayers(myGame.g_Players);
                                InitMainMenu(myGame.g_Widgets);
                                break;
                            default:
                                SetActorDirection(&myGame.g_Actors[ACT_INDEX_PADDLE1], none);
                                break;
                        }
                        BallMovement(&myGame, nbActors);
                        break;
                    case Closed:
                        break;
                    default:
                        break;
                }
                RenderingAll(&myGame, nbActors, nbWidgets);
                SDL_Delay(10);
            }
            frameLimit = SDL_GetTicks() + MAXIMAGEPS;  //1/60(FPS) * 1000 = 16.6
            SDL_Delay(2000);

        }else
        {
            appState = EXIT_FAILURE;
        }
    }else
    {
        appState = EXIT_FAILURE;
    }
    //Freeing memory
    Destroy(&myGame, &nbActors, &nbWidgets);
    nbWidgets = 1;
    FreeWidgets(currentWidget, &nbWidgets);
    SDL_Quit();

    return appState;
}

