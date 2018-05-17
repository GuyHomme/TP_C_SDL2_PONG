#ifndef DEF_WIDGET

#define DEF_WIDGET

#include <SDL2/SDL.h>
#include "color.h"

typedef struct Widget
{
    int m_id;
    SDL_Rect *m_body;
    RGBA m_color;
    //Add text ?
}Widget;

extern void WidgetConstruct(Widget *tWidget, int id, SDL_Rect tBody, RGBA color);

#endif // DEF_WIDGET
