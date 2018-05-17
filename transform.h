/*
    Useful for basic transform operations, such as points, axis, and SDL_Rect because its SDL based
*/
#ifndef DEF_TRANSFORM

#define DEF_TRANSFORM

#include <SDL2\SDL.h>

typedef enum Axis   //Handles the different 2D axis
{
    x, y, xy
}Axis;

typedef struct RawPoint //Handles a point made up by integer values
{
    int m_x;
    int m_y;
}RawPoint;

typedef struct Point    //Handles a point made up by float values
{
    float m_x;
    float m_y;
}Point;

//CONVERSIONS
//All the functions aiming to convert and/or apply it to variables pointed by argument pointers
extern RawPoint RawPointConstruct(int x, int y);
/*
    Return a temporary RawPoint created by 2 integers in arguments
*/
extern Point PointConstruct(float x, float y);
/*
    Return a temporary Point created by 2 floats in arguments
*/
extern SDL_Rect CreateRectFromRawPoints(RawPoint position, RawPoint tSize);
/*
    Return a temporary SDL_Rect created by a RawPoint as position, and another one as tSize
*/
extern RawPoint TranslateVector2D(RawPoint point1, RawPoint point2);
/*
    Return a RawPoint that is the addition of 2 other RawPoints
*/

//ACCESSORS
//All the functions aiming to access the values of structures
extern RawPoint GetRectSize(SDL_Rect rect);
/*
    Return a RawPoint containing the rect size (width and height)
*/
extern RawPoint GetRectCenterPosition(SDL_Rect targetRect);
/*
    Return a RawPoint containing the targetRect centered position (not the up-left one, that is returned by GetRectRoughPosition)
*/
extern RawPoint GetRectRoughPosition(SDL_Rect targetRect);
/*
    Return a RawPoint containing the targetRect up-left position
*/

//MUTATORS
//All the functions aiming to set the values of structures
extern void SetRawPointInt(RawPoint* targetPoint, int x, int y);
/*
    Set the values of targetPoint (RawPoint (int)) with the x and y arguments
*/
extern void SetPointInt(Point* targetPoint, int x, int y);
/*
    Set the values of targetPoint (Point (float)) with the x and y arguments
*/
extern void SetPointFloat(Point* targetPoint, float x, float y);
/*
    Set the values of targetPoint (Point (float)) with the x and y arguments
*/
extern void SetRectPosition(SDL_Rect *targetRect, RawPoint newPos);
/*
    Set the position of targetRect (SDL_Rect) with the RawPoint argument newPos
*/
extern void SetRectSize(SDL_Rect *targetRect, RawPoint rectSize);
/*
    Set the size of targetRect (SDL_Rect) with the RawPoint argument rectSize
*/
extern void SetRectSizeRough(SDL_Rect *targetRect, int width, int height);
/*
    Set the size of targetRect (SDL_Rect) with the rough integer arguments width and height
*/
extern void MoveRectToRawPoint(SDL_Rect *targetRect, RawPoint position);
/*
    Set the position of targetRect (SDL_Rect), and does the exact same thing than the SetRectPosition function...
*/
extern void MoveRectToCoords(SDL_Rect *targetRect, int targetX, int targetY);
/*
    Set the position of targetRect (SDL_Rect) with the rough integer arguments targetX and targetY
*/

//TESTS
//All the functions aiming to return results from tests (mainly bools)
extern int RectOutRange(SDL_Rect rect, RawPoint srcLimit, RawPoint dstLimit);
/*
    Return the test checking if rect (SDL_Rect) is out of the range made by the rectangle with source point as srcLimit and end point as dstLimit (RawPoints)
*/
extern int RawPointOutRange(RawPoint point, RawPoint srcLimit, RawPoint dstLimit);
/*
    Return the test checking if point (RawPoint) is out of the range made by the rectangle with source point as srcLimit and endPoint as dstLimit (RawPoints)
*/

#endif // DEF_TRANSFORM
