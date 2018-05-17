#include "gameplay.h"

void AiFollowBall(Game *myGame, int nbActors)
{
    FollowActor(&myGame->g_Actors[ACT_INDEX_PADDLE2], myGame->g_Actors[ACT_INDEX_BALL], myGame->g_Actors, nbActors, y, RawPointConstruct(0,0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT -1));
}

void BallMovement(Game *myGame, int nbActors)
{
    Collision tCol = ActorMovement(&myGame->g_Actors[ACT_INDEX_BALL], myGame->g_Actors, nbActors, myGame->g_Actors[ACT_INDEX_BALL].m_speed,
                                     RawPointConstruct(0,0),
                                     RawPointConstruct(SCREEN_WIDTH , SCREEN_HEIGHT)
                                  );

    switch(tCol.m_infos)
    {
        case col_Other:
                switch(ActorClosestFromLimit(myGame->g_Actors[ACT_INDEX_BALL], RawPointConstruct(0,0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT -1)))
                {
                case up:
                    switch(myGame->g_Actors[ACT_INDEX_BALL].m_direction)
                    {
                    case up:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], down);
                        break;
                    case up_right:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], down_right);
                        break;
                    case up_left:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], down_left);
                        break;
                    default:
                        break;
                    }
                    break;
                case down:
                    switch(myGame->g_Actors[ACT_INDEX_BALL].m_direction)
                    {
                    case down:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], up);
                        break;
                    case down_right:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], up_right);
                        break;
                    case down_left:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], up_left);
                        break;
                    default:
                        break;
                    }
                    break;
                case left:
                    SpawnBall(&myGame->g_Actors[ACT_INDEX_BALL]);
                    IncrementPlayerScore(&myGame->g_Players[INDEX_PLAYER2]);
                    printf("Player 2 score : %d\n", myGame->g_Players[INDEX_PLAYER2].m_score);
                    break;
                case right:
                    SpawnBall(&myGame->g_Actors[ACT_INDEX_BALL]);
                    IncrementPlayerScore(&myGame->g_Players[INDEX_PLAYER1]);
                    printf("Player 1 score : %d\n", myGame->g_Players[INDEX_PLAYER1].m_score);
                    break;
                default:
                    break;
                }
            break;
        case col_Actor:
                switch(ActorClosestFromLimit(myGame->g_Actors[ACT_INDEX_BALL], RawPointConstruct(0,0), RawPointConstruct(SCREEN_WIDTH - 1, SCREEN_HEIGHT -1)))
                {
                case left:
                    switch(myGame->g_Actors[ACT_INDEX_BALL].m_direction)
                    {
                    case left:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], right);
                        break;
                    case up_left:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], up_right);
                        break;
                    case down_left:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], down_right);
                        break;
                    default:
                        break;
                    }
                    break;
                case right:
                    switch(myGame->g_Actors[ACT_INDEX_BALL].m_direction)
                    {
                    case right:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], left);
                        break;
                    case down_right:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], down_left);
                        break;
                    case up_right:
                        SetActorDirection(&myGame->g_Actors[ACT_INDEX_BALL], up_left);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
    }
}
