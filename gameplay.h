/*
    Useful for handling gameplay elements through every other function
*/
#ifndef DEF_GAMEPLAY

#define DEF_GAMPELAY

#include "game.h"
#include "player.h"
#include "stdio.h"

extern void AiFollowBall(Game *myGame, int nbActors);
/*
    Make the paddle2 actor contained in myGame structure following the ball actor
*/
extern void BallMovement(Game *myGame, int nbActors);
/*
    Handle the ball actor contained in myGame structure such as bouncing, re-spawning and so on
*/

#endif // DEF_GAMEPLAY
