#include "player.h"

//MUTATORS
void SetPlayerScore(Player *tempPlayer, int score)
{
    tempPlayer->m_score = score;
}

void IncrementPlayerScore(Player *tempPlayer)
{
    tempPlayer->m_score ++;
}

void DecrementPlayerScore(Player *tempPlayer)
{
    if(tempPlayer->m_score > 0)
    {
        tempPlayer->m_score --;
    }
}
