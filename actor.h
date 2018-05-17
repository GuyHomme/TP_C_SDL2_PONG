/*
    Useful for handling all entities that are supposed to move and have a visual representation
*/
#ifndef DEF_BALL

#define DEF_BALL

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "transform.h"
#include "color.h"


typedef enum Collider   //Handling all the states that a collider can be
{
    col_Void, col_Actor, col_Other
}Collider;

typedef enum Direction  //Handling all the directions that an actor can move along
{
    up, up_right, right, down_right, down, down_left, left, up_left, none
}Direction;

typedef struct Actor    //Actor structure, defined by an ID, a SDL_Rect, direction, speed and color
{
    int m_id;
    SDL_Rect *m_body;
    Direction m_direction;
    float m_speed;
    RGBA m_color;
}Actor;

typedef struct Collision    //Collision structure, contains collider infos, and actor ID
{
    Collider m_infos;
    int m_actorId;
}Collision;

//MUTATORS
//All the function aiming to set the values of structures
extern void ActorConstruct(Actor *tActor, int id, SDL_Rect tBody, Direction tDirection, float tSpeed, RGBA color);
/*
    Set all tActor values from id, tBody, tDirection, tSpeed and color parameters
*/
extern void SetActorSpeed(Actor *theActor, float newSpeed);
/*
    Set theActor speed from newSpeed parameter
*/
extern void SetActorDirection(Actor *theActor, Direction newDirection);
/*
    Set theActor direction from newDirection parameter
*/
extern void SetActorBody(Actor *theActor, SDL_Rect newBody);
/*
    Set theActor body from newBody parameter
*/
extern void SetActorBodyPosition(Actor *theActor, RawPoint newPosition);
/*
    Set theActor body rough position from newPosition
*/

//ACCESSORS
//All the functions aiming to access structure values
extern RawPoint GetActorBodySize(Actor theActor);
/*
    Return the body size as RawPoint of theActor
*/
extern RawPoint GetActorBodyPosition(Actor theActor);
/*
    Return the body position as RawPoint of theActor
*/

//MEMORY
//All the functions aiming to handle memory such as allocating and freeing actor memory
extern void FreeActor(Actor *actor);
/*
    Free all the memory used by actor if it is not NULL
*/

//MOVEMENT
//All the functions aiming to handle actor movements
extern void FollowActor(Actor *follower, Actor target, Actor *gameActors, int nbActors, Axis axis, RawPoint srcLimit, RawPoint dstLimit);
/*
    Make follower (Actor) following target (Actor) on the chosen axis (Axis).
    Verification values are passed as arguments such as gameActors, nbActors to check for collisions and srcLimit and dstLimit for the screen limits.
*/
extern Collision ActorMovement(Actor *theActor, Actor *gameActors, int nbActors, float speed, RawPoint srcLimit, RawPoint dstLimit);
/*
    Make theActor (Actor) moving along his direction value, this function calls ActorPrimaryMovement by checking each enum Direction value.
    For example : If the direction is up_right, it'll first call ActorPrimaryMovement, with up direction, and then with the right direction.

    Verification values are passed as arguments such as gameActors, nbActors to check for collisions and srcLimit and dstLimit for the screen limits.
*/
extern void ActorPrimaryMovement(Actor *theActor, float speed, Direction direction);
/*
    Make theActor (Actor) moving along the PRIMARY direction, it means that it only makes the actor moving along the 4 primitive directions (up, right, left, down),
    it does not handle the combined directions.
*/

//TESTS
//All the functions aiming to check tests (mainly booleans and pointers)
extern Direction ActorClosestFromLimit(Actor theActor, RawPoint srcLimit, RawPoint dstLimit);
/*
    Return a Direction enum value that indicates the closest limit from theActor (Actor) considering srcLimit and dstLimit
*/
extern Collision ActorCollision(Actor theActor, Actor *gameActors, int nbActors, RawPoint srcLimit, RawPoint dstLimit);
/*
    Return a Collision enum value that indicates the type of collider theActor (Actor) encounters with his current position
*/
extern Actor* ActorOverlappingAny(Actor theActor, Actor *gameActors, int nbActors);
/*
    Return the address of the actor (if there's any) that theActor (Actor) is currently overlapping
*/
extern int IsPrimaryDir(Direction dir, Direction sample);
/*
    Return the test checking if sample (Direction) is part of dir (Direction)
*/
extern int ActorOutRange(Actor theActor, RawPoint srcLimit, RawPoint dstLimit);
/*
    Return the test checking if theActor (Actor) is out of the range made up by the rectangle srcLimit to dstLimit
*/
#endif
