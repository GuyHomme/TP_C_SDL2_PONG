#include "actor.h"

//MUTATORS

void ActorConstruct(Actor *tActor, int id, SDL_Rect tBody, Direction tDirection, float tSpeed, RGBA color)
{
    tActor->m_id = id;
    *tActor->m_body = tBody;
    tActor->m_direction = tDirection;
    tActor->m_speed = tSpeed;
    tActor->m_color = color;
}

void SetActorSpeed(Actor *theActor, float newSpeed)
{
    theActor->m_speed = newSpeed;
}

void SetActorDirection(Actor *theActor, Direction newDirection)
{
    theActor->m_direction = newDirection;
}

void SetActorBody(Actor *theActor, SDL_Rect newBody)
{
    theActor->m_body = &newBody;
}

void SetActorBodyPosition(Actor *theActor, RawPoint newPosition)
{
    SetRectPosition(theActor->m_body, newPosition);
}

//ACCESSORS

RawPoint GetActorBodySize(Actor theActor)
{
    return GetRectSize(*theActor.m_body);
}

RawPoint GetActorBodyPosition(Actor theActor)
{
    return GetRectRoughPosition(*theActor.m_body);
}

//MOVEMENT

void FollowActor(Actor *follower, Actor target, Actor *gameActors, int nbActors, Axis axis, RawPoint srcLimit, RawPoint dstLimit)
{
    float tempSpeed = 1.0f;
    switch(axis)
    {
        case x:
            if(follower->m_body->x != target.m_body->x)
            {
                if(follower->m_body->x > target.m_body->x)
                {
                    tempSpeed = ((follower->m_body->x - follower->m_speed) > target.m_body->x) ? follower->m_speed : (float)target.m_body->x;
                    SetActorDirection(follower, left);
                }else
                {
                    tempSpeed = ((follower->m_body->x + follower->m_speed) < target.m_body->x) ? follower->m_speed : (float)target.m_body->x;
                    SetActorDirection(follower, right);
                }
            }else
                tempSpeed = -1.0f; //Already at target
            break;

        case y:
            if(follower->m_body->y != target.m_body->y)
            {
                if(follower->m_body->y > target.m_body->y)
                {
                    //tempSpeed = ((follower->m_body->y - follower->m_speed) > target.m_body->y) ? follower->m_speed : (float)target.m_body->y;
                    tempSpeed = 2.0f;
                    SetActorDirection(follower, up);
                }else
                {
                    //tempSpeed = ((follower->m_body->y + follower->m_speed) < target.m_body->y) ? follower->m_speed : (float)target.m_body->y;
                    tempSpeed = 2.0f;
                    SetActorDirection(follower, down);
                }
            }else
                tempSpeed = -1.0f; //Already at target
            break;
        default:
            tempSpeed = -1.0f;
            break;
    }
    if(tempSpeed > 0.0f)
    {
        ActorMovement(follower, gameActors, nbActors, 2.0f, srcLimit, dstLimit);
    }
}

Collision ActorMovement(Actor *theActor, Actor *gameActors, int nbActors, float speed, RawPoint srcLimit, RawPoint dstLimit)
{
    RawPoint origin = GetRectRoughPosition(*theActor->m_body);
    Collision newCollision = {col_Void, -1};
    int canMove = 0;

    switch(theActor->m_direction)
    {
        case up_left:
            ActorPrimaryMovement(theActor, speed, up);
            newCollision = ActorCollision(*theActor, gameActors, nbActors, srcLimit, dstLimit);
            if((canMove = (newCollision.m_infos == col_Void)))
            {
                origin = GetRectRoughPosition(*theActor->m_body);
                ActorPrimaryMovement(theActor, speed, left);
            }
            break;
        case up:
            ActorPrimaryMovement(theActor, speed, up);
            break;
        case up_right:
            ActorPrimaryMovement(theActor, speed, up);
            newCollision = ActorCollision(*theActor, gameActors, nbActors, srcLimit, dstLimit);
            if((canMove = (newCollision.m_infos == col_Void)))
            {
                origin = GetRectRoughPosition(*theActor->m_body);
                ActorPrimaryMovement(theActor, speed, right);
            }
            break;
        case right:
            ActorPrimaryMovement(theActor, speed, right);
            break;
        case down_right:
            ActorPrimaryMovement(theActor, speed, down);
            newCollision = ActorCollision(*theActor, gameActors, nbActors, srcLimit, dstLimit);
            if((canMove = (newCollision.m_infos == col_Void)))
            {
                origin = GetRectRoughPosition(*theActor->m_body);
                ActorPrimaryMovement(theActor, speed, right);
            }
            break;
        case down:
            ActorPrimaryMovement(theActor, speed, down);
            break;
        case down_left:
            ActorPrimaryMovement(theActor, speed, down);
            newCollision = ActorCollision(*theActor, gameActors, nbActors, srcLimit, dstLimit);
            if((canMove = (newCollision.m_infos == col_Void)))
            {
                origin = GetRectRoughPosition(*theActor->m_body);
                ActorPrimaryMovement(theActor, speed, left);
            }
            break;
        case left:
            ActorPrimaryMovement(theActor, speed, left);
            break;
        default:
            break;
    }
    //printf("DST X : %d. ACTOR X : %d.\n", dstLimit.m_x, theActor->m_body->x + theActor->m_body->w);
    newCollision = ActorCollision(*theActor, gameActors, nbActors, srcLimit, dstLimit);
    canMove = newCollision.m_infos == col_Void;
    if(!canMove)
        SetActorBodyPosition(theActor, origin);

    return newCollision;
}

void ActorPrimaryMovement(Actor *theActor, float speed, Direction direction)
{
        switch(direction)
        {
            case up:
                   SetActorBodyPosition(theActor,TranslateVector2D(GetRectRoughPosition(*theActor->m_body),
                                                          RawPointConstruct(0, (int)(-speed))
                                                          ));
                break;
            case right:
                    SetActorBodyPosition(theActor,TranslateVector2D(GetRectRoughPosition(*theActor->m_body),
                                                           RawPointConstruct((int)(speed), 0)
                                                           ));
                break;
            case down:
                    SetActorBodyPosition(theActor,TranslateVector2D(GetRectRoughPosition(*theActor->m_body),
                                                           RawPointConstruct(0, (int)(speed))
                                                           ));
                break;
            case left:
                    SetActorBodyPosition(theActor,TranslateVector2D(GetRectRoughPosition(*theActor->m_body),
                                                           RawPointConstruct((int)(-speed), 0)
                                                           ));
                break;
            default:
                break;
        }
}

//TESTS
Direction ActorClosestFromLimit(Actor theActor, RawPoint srcLimit, RawPoint dstLimit)
{
    if(GetActorBodyPosition(theActor).m_x < (dstLimit.m_x - GetActorBodyPosition(theActor).m_x))
    {
        if((dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_x) < GetActorBodyPosition(theActor).m_y)
        {
            return ((dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y) < GetActorBodyPosition(theActor).m_x) ? down : left;
        }else if(GetActorBodyPosition(theActor).m_y < (dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y))
        {
            return (GetActorBodyPosition(theActor).m_y < GetActorBodyPosition(theActor).m_x) ? up : left;
        }
    }
    else if((dstLimit.m_x - GetActorBodyPosition(theActor).m_x + GetActorBodySize(theActor).m_x) < GetActorBodyPosition(theActor).m_x)
    {
        if((dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_x) < GetActorBodyPosition(theActor).m_y)
        {
            return ((dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y) < (dstLimit.m_x - GetActorBodyPosition(theActor).m_x + GetActorBodySize(theActor).m_x)) ? down : right;
        }else if(GetActorBodyPosition(theActor).m_y < (dstLimit.m_y - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y))
        {
            return (GetActorBodyPosition(theActor).m_y < (dstLimit.m_x - GetActorBodyPosition(theActor).m_x + GetActorBodySize(theActor).m_x)) ? up : right;
        }
    }
    return none;
    /*
    return (
            ((dstLimit.m_x - GetActorBodyPosition(theActor).m_x + GetActorBodySize(theActor).m_x) < GetActorBodyPosition(theActor).m_x)
            ? right
            : (GetActorBodyPosition(theActor).m_x < (dstLimit.m_y - 1 - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y))
               ? left
               : ((dstLimit.m_y - 1 - GetActorBodyPosition(theActor).m_y + GetActorBodySize(theActor).m_y) <  GetActorBodyPosition(theActor).m_y
                  ? down
                  : up)
            );*/
}

Collision ActorCollision(Actor theActor, Actor *gameActors, int nbActors, RawPoint srcLimit, RawPoint dstLimit)
{
    Collision newCollision = {col_Void, -1}; //= CreateCollisionObject();
    Actor *OverlappedActor = NULL;

    if(ActorOutRange(theActor, srcLimit, dstLimit))
    {
        newCollision.m_actorId = -1;
        newCollision.m_infos = col_Other;
    }else
    {
        OverlappedActor = ActorOverlappingAny(theActor, gameActors, nbActors);
        if(OverlappedActor != NULL)
        {
            newCollision.m_actorId = OverlappedActor->m_id;
            newCollision.m_infos = col_Actor;
        }
    }
    return newCollision;
}

int ActorOutRange(Actor theActor, RawPoint srcLimit, RawPoint dstLimit)
{
    return(RectOutRange(*theActor.m_body, srcLimit, dstLimit));
}

int IsPrimaryDir(Direction dir, Direction sample)
{
    switch(dir)
    {
    case up:
        return (sample == up || sample == up_left || sample == up_right);
    case down:
        return (sample == down || sample == down_left || sample == down_right);
    case right:
        return (sample == right || sample == down_right || sample == up_right);
    case left:
        return (sample == left || sample == up_left || sample == down_left);
    default:
        return 0;
    }
}

Actor* ActorOverlappingAny(Actor theActor, Actor *gameActors, int nbActors)
{
    int i = 0;

    for(i = 0 ; i < nbActors ; i++)
    {
        if(theActor.m_id != gameActors[i].m_id)
        {
            if(SDL_HasIntersection(theActor.m_body, gameActors[i].m_body))
                return &gameActors[i];
        }
    }
    return NULL;
}

//MEMORY

void FreeActor(Actor *actor)
{
    Actor* tempActor = actor;

    if(tempActor != NULL)
    {
        if(actor->m_body != NULL)
            SDL_free(actor->m_body);
        free(actor);
    }
}



