/*
    Useful to handle the colors with simple structures
*/
#ifndef DEF_COLOR

#define DEF_COLOR

#include <SDL2/SDL.h>

typedef struct RGBA //Color Red, Blue, Green, Alpha
{
    int m_R;
    int m_G;
    int m_B;
    int m_A;
}RGBA;

typedef struct RGB //Color Red, Blue, Green
{
    int m_R;
    int m_G;
    int m_B;
}RGB;

extern RGBA RGBAConstruct(int R, int G, int B, int A);
/*
    Return a temporary RGBA value from R, G, B, and A integer parameters
*/
extern RGB RGBConstruct(int R, int G, int B);
/*
    Return a temporary RGB value from R, G, B integer parameters
*/
extern RGBA RGBA_Green();
/*
    Return a Green RGBA color
*/
extern RGBA RGBA_Red();
/*
    Return a Red RGBA color
*/
extern RGBA RGBA_Black();
/*
    Return a Black RGBA color
*/
extern RGBA RGBA_Blue();
/*
    Return a Blue RGBA color
*/
extern RGBA RGBA_White();
/*
    Return a White RGBA color
*/

#endif // DEF_COLOR
