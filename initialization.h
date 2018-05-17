/*
    Useful for initializing values of in scenes, such as widgets in the main menu, actors in play mode, re-spawning
*/
#ifndef DEF_INIT

#define DEF_INIT

#include "actor.h"
#include "widget.h"
#include "game.h"

extern void InitMainMenu(Widget *widgets);
/*
    Initialize the properties of the main menu scene widgets, id, position, color
*/
extern void SpawnBall(Actor *ball);
/*
    Initialize the properties of the ball actor with a random direction, id, position, color
*/
extern void InitMainActors(Actor *actors);
/*
    Initialize the properties of the play mode scene actors, id, position, color
*/

#endif // DEF_INIT
