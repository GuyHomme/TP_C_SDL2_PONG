/*
    Useful for handling Player data
*/
#ifndef DEF_PLAYER

#define DEF_PLAYER

#include <string.h>

#include <stdlib.h>

#define PLAYER_MAX_NAME_SIZE 20

typedef struct Player   //Handling player infos, such as score
{
    int m_score;
}Player;


//MUTATORS
//All functions aiming to Set player data
extern void SetPlayerScore(Player *tempPlayer, int score);
/*
    Set tempPlayer (Player) score from score parameter
*/
extern void IncrementPlayerScore(Player *tempPlayer);
/*
    Increment tempPlayer score
*/
extern void DecrementPlayerScore(Player *tempPlayer);
/*
    Decrement templPlayer score
*/

#endif // DEF_PLAYER
