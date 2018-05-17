#include "transform.h"

//CONVERSIONS
RawPoint RawPointConstruct(int x, int y)
{
    RawPoint tempPoint = {x, y};

    return tempPoint;
}

Point PointConstruct(float x, float y)
{
    Point tempPoint = {x, y};

    return tempPoint;
}

SDL_Rect CreateRectFromRawPoints(RawPoint position, RawPoint tSize)
{
    SDL_Rect tempRect;

    tempRect.x = position.m_x;
    tempRect.y = position.m_y;
    tempRect.w = tSize.m_x;
    tempRect.h = tSize.m_y;

    return tempRect;
}

RawPoint TranslateVector2D(RawPoint point1, RawPoint point2)
{
    RawPoint tempPoint = {point1.m_x + point2.m_x, point1.m_y + point2.m_y};

    return tempPoint;
}

//ACCESSORS
RawPoint GetRectSize(SDL_Rect rect)
{
    RawPoint newSize = {rect.w, rect.h};

    return newSize;
}

RawPoint GetRectCenterPosition(SDL_Rect targetRect)
{
    RawPoint tempPoint = {targetRect.w + targetRect.x, targetRect.h + targetRect.y};

    return(tempPoint);
}

RawPoint GetRectRoughPosition(SDL_Rect targetRect)
{
    RawPoint tempPoint = {targetRect.x, targetRect.y};

    return tempPoint;
}

//MUTATORS
void SetRawPointInt(RawPoint* targetPoint, int x, int y)
{
    targetPoint->m_x = x;
    targetPoint->m_y = y;
}

void SetPointInt(Point* targetPoint, int x, int y)
{
    targetPoint->m_x = (float)x;
    targetPoint->m_y = (float)y;
}

void SetPointFloat(Point* targetPoint, float x, float y)
{
    targetPoint->m_x = x;
    targetPoint->m_y = y;
}

void SetRectPosition(SDL_Rect *targetRect, RawPoint newPos)
{
    targetRect->x = newPos.m_x;
    targetRect->y = newPos.m_y;
}

void SetRectSize(SDL_Rect *targetRect, RawPoint rectSize)
{
    targetRect->w = rectSize.m_x;
    targetRect->h = rectSize.m_y;
}

void SetRectSizeRough(SDL_Rect *targetRect, int width, int height)
{
    targetRect->w = width;
    targetRect->h = height;
}

void MoveRectToRawPoint(SDL_Rect *targetRect, RawPoint position)
{
    targetRect->x = position.m_x;
    targetRect->y = position.m_y;
}

void MoveRectToCoords(SDL_Rect *targetRect, int targetX, int targetY)
{
    targetRect->x = targetX;
    targetRect->y = targetY;
}

//TESTS
int RawPointOutRange(RawPoint point, RawPoint srcLimit, RawPoint dstLimit)
{
    return(point.m_x < srcLimit.m_x || point.m_y < srcLimit.m_y || point.m_x >= dstLimit.m_x || point.m_y >= dstLimit.m_y);
}

int RectOutRange(SDL_Rect rect, RawPoint srcLimit, RawPoint dstLimit)
{
    return(RawPointOutRange(GetRectRoughPosition(rect), srcLimit, dstLimit) ||
           RawPointOutRange(TranslateVector2D(GetRectRoughPosition(rect), GetRectSize(rect)),
                             srcLimit, dstLimit)
           );
}
