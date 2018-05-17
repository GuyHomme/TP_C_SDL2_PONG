#include "widget.h"

void WidgetConstruct(Widget *tWidget, int id, SDL_Rect tBody, RGBA color)
{
    tWidget->m_id = id;
    *tWidget->m_body = tBody;
    tWidget->m_color = color;
}
