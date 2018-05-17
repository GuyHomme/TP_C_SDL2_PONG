#include "initialization.h"

void InitMainMenu(Widget *widgets)
{
    //Play button
    WidgetConstruct(&widgets[WID_INDEX_PLAY_SOLO],
                    WID_INDEX_PLAY_SOLO,
                    CreateRectFromRawPoints(
                                            RawPointConstruct(SCREEN_WIDTH/2 - MENU_WIDGET_WIDTH/2 - 1, SCREEN_HEIGHT/NB_MIN_MENU_WIDGETS - MENU_WIDGET_HEIGHT - 1),
                                            RawPointConstruct(MENU_WIDGET_WIDTH, MENU_WIDGET_HEIGHT)
                                            ),
                    RGBA_White()
                    );

    //Play button
    WidgetConstruct(&widgets[WID_INDEX_PLAY_MULTI],
                    WID_INDEX_PLAY_MULTI,
                        CreateRectFromRawPoints(
                                                RawPointConstruct(SCREEN_WIDTH/2 - MENU_WIDGET_WIDTH/2 - 1, (SCREEN_HEIGHT/NB_MIN_MENU_WIDGETS)*2  - MENU_WIDGET_HEIGHT - 1),
                                                RawPointConstruct(MENU_WIDGET_WIDTH, MENU_WIDGET_HEIGHT)
                                                ),
                    RGBA_Blue()
                    );
    //Leave button
    WidgetConstruct(&widgets[WID_INDEX_LEAVE],
                    WID_INDEX_LEAVE,
                        CreateRectFromRawPoints(
                                                RawPointConstruct(SCREEN_WIDTH/2 - MENU_WIDGET_WIDTH/2 - 1, (SCREEN_HEIGHT/NB_MIN_MENU_WIDGETS)*3  - MENU_WIDGET_HEIGHT - 1),
                                                RawPointConstruct(MENU_WIDGET_WIDTH, MENU_WIDGET_HEIGHT)
                                                ),
                    RGBA_Red()
                    );
}

void SpawnBall(Actor *ball)
{
    ActorConstruct(ball,
                   0,
                   CreateRectFromRawPoints(
                                           RawPointConstruct(SCREEN_WIDTH/2 - BALL_WIDTH/2 - 1, SCREEN_HEIGHT/2 - BALL_HEIGHT/2 -1),
                                           RawPointConstruct(BALL_WIDTH, BALL_HEIGHT)
                                           ), (Direction)(rand()%2)? up_right : up_left, BALL_SPEED, RGBA_White()
                   );
}

void InitMainActors(Actor *actors)
{
    //Setting ball actor
    SpawnBall(&actors[ACT_INDEX_BALL]);
    //Setting first paddle actor
    ActorConstruct(&actors[ACT_INDEX_PADDLE1],
                   1,
                   CreateRectFromRawPoints(
                                           RawPointConstruct(1, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 - 1),
                                           RawPointConstruct(PADDLE_WIDTH - 1, PADDLE_HEIGHT)
                                           ), none, PADDLE_SPEED, RGBA_Green()
                   );
    //Setting first paddle actor
    ActorConstruct(&actors[ACT_INDEX_PADDLE2],
                   2,
                   CreateRectFromRawPoints(
                                           RawPointConstruct(SCREEN_WIDTH - PADDLE_WIDTH - 1, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2 - 1),
                                           RawPointConstruct(PADDLE_WIDTH - 1, PADDLE_HEIGHT)
                                           ), none, PADDLE_SPEED, RGBA_Red()
                   );
}
