#include "color.h"

RGBA RGBAConstruct(int R, int G, int B, int A)
{
    RGBA tempRGBA = {R, G, B, A};

    return tempRGBA;
}

RGB RGBConstruct(int R, int G, int B)
{
    RGB tempRGB = {R, G, B};

    return tempRGB;
}

RGBA RGBA_Black()
{
    RGBA tempRGBA = {0, 0, 0, 255};

    return tempRGBA;
}

RGBA RGBA_Red()
{
    RGBA tempRGBA = {255, 0, 0, 255};

    return tempRGBA;
}

RGBA RGBA_Blue()
{
    RGBA tempRGBA = {0, 0, 255, 255};

    return tempRGBA;
}

RGBA RGBA_Green()
{
    RGBA tempRGBA = {0, 255, 0, 255};

    return tempRGBA;
}

RGBA RGBA_White()
{
    RGBA tempRGBA = {255, 255, 255, 255};

    return tempRGBA;
}
