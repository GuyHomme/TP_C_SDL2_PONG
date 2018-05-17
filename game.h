/*
    Useful for all the motor and main functions of the game such as Rendering, Allocation, Memory, and Structures handling
*/
#ifndef DEF_GAME

#define DEF_GAME

#include <SDL2\SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "actor.h"
#include "widget.h"
#include "player.h"

//DIMENSIONS & PROPERTIES

#define MENU_WIDGET_WIDTH 80
#define MENU_WIDGET_HEIGHT 30

#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 75
#define PADDLE_SPEED 15.0f

#define BALL_WIDTH 25
#define BALL_HEIGHT 25
#define BALL_SPEED 3.0f

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

//STANDARDS
#define NB_PLAYERS 2
#define NB_MIN_MENU_WIDGETS 3

#define INDEX_PLAYER1 0 //Index in array
#define INDEX_PLAYER2 1

#define WID_INDEX_PLAY_SOLO 0
#define WID_INDEX_PLAY_MULTI 1
#define WID_INDEX_LEAVE 2

#define NB_MIN_ACTORS 3 //3 actors minimum, 2 paddles and 1 ball. Useful for the game initialization

#define ACT_INDEX_BALL 0    //Index in array
#define ACT_INDEX_PADDLE1 1
#define ACT_INDEX_PADDLE2 2

#define MIN0 0
#define MIN1 1
#define MAXIMAGEPS 16   //1/60(FPS) * 1000 = 16.6

typedef struct MouseInfos   //Handles the rectangle of the mouse cursor
{
    SDL_Rect *m_body;
}MouseInfos;

typedef enum GameState //Handles the current state of the game
{
    Closed, Running, Paused
}GameState;

typedef enum GameMode   //Handles the current game mode of the game
{
    None, Menu, Solo, Multi
}GameMode;

typedef enum InEvent    //Handles the inputs needed for the game
{
    mouse_click, key_up, key_down, key_z, key_s, key_esc, force_quit, no_event
}InEvent;

typedef struct Game     //Main structure of the game, handling memory, states, actors, and so on
{
        SDL_Window *g_pWindow;
        SDL_Renderer *g_pRenderer;
        SDL_Texture *g_pTexture;
        GameState g_State;
        GameMode g_Mode;
        Actor *g_Actors;
        Widget *g_Widgets;
        Player *g_Players;
        MouseInfos *g_mouseInfos;
}Game;

//MEMORY
    //All the functions aiming to handle memory, such as allocation or free
extern void FreeCursor(MouseInfos *mouse);
/*
    Free the memory allocated by a MouseInfos structure if mouse is not equal to NULL
*/
extern void FreeWidgets(Widget *widgets, int *nbWidgets);
/*
    Free the memory allocated by a Widget pointer if it is not equal to NULL,
    the number of widgets is specified by nbWidgets and is set to 0 when the widgets are freed
*/
extern void FreeActors(Actor *actors, int *nbActors);
/*
    Free the memory allocated by an Actor pointer if it is not equal to NULL,
    the number of actors is specified by nbActors, and is set to 0 when the actors are freed
*/
extern void FreePlayers(Player *players);
/*
    Free the memory allocated by a Player pointer if it is not equal to NULL
*/
extern void Destroy(Game *myGame, int *nbActors, int *nbWidgets);
/*
    Free all the memory allocated by a Game pointer, the number of actors and widgets are specified by the int pointers corresponding (nbActors and nbWidgets).
    For each pointer freed, the corresponding integer (such as nbActors and nbWidgets) is set to 0
*/
    //INIT
extern int Init(char *title, int xpos, int ypos, int width, int height, int flags, Game *myGame);
/*
    Initialize each SDL variable of a Game structure like the window, initialized with the title, x position, y position, width, and height.
    Flags is an "optional" parameter used for more options
*/

//RENDERING
//All the functions aiming to render the visual effects driven by SDL variables on screen
extern void RenderingAll(Game *myGame, int nbActors, int nbWidgets);
/*
    Render all the visual elements of a Game structure (mainly actors and widgets that the number is specified by nbActors and nbWidgets)
*/
extern void RenderingAllWidgets(Game *myGame, int nbWidgets);
/*
    Render all the visual elements of widgets pointed by a Widget pointer and contained in a Game structure, the number of widgets is specified by nbWidgets
*/
extern void RenderingAllActors(Game *myGame, int nbActors);
/*
    Render all the visual elements of actors pointed by an Actor pointer and contained in a Game structure, the number of actors is specified by nbActors
*/

//MENUS HANDLER
//All the functions aiming to navigate between the scenes of a game
extern int EnterPlayMode(Game *myGame, int nbActors, int boolSolo);
/*
    Initialize all the variables of a Game structure for the play mode,
    such as allocating all the memory needed for the actors, and freeing previous scene memory (such as widgets),
    boolSolo specifies if the game mode is solo or multi.
*/
extern int EnterMainMenu(Game *myGame, int nbWidgets);
/*
    Initialize all the variables of a Game structure for the menu,
    such as allocating all the memory needed for the widgets, and freeing previous scene memory (such as actors).
*/
extern int LeaveGame(Game *myGame);
/*
    Only changes the state and mode of a Game structure to prevent the program that the game should exit.
*/

//UTILITIES
//All the functions aiming to be useful for other functionalities
extern Widget* TryFocusOnWidget(Game *myGame, int nbWidgets);
/*
    If a widget is aimed by the MouseInfo body contained in myGame when this function is called, the address of the widget is returned, if none,
    NULL is returned.
*/
extern void Delay(unsigned int frameLimit);
/*
    Operate a delay if frameLimit ms on the execution thread
*/
extern InEvent HandleEvents(Game *myGame);
/*
    Return the corresponding enum value of InEvent depending on the event returned by the SDL_Event variable.
    If the event is a mouse button down, the body of the myGame MouseInfos is moved to its coordinates.
*/

#endif // DEF_GAME
