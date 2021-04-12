
#pragma once

#include <math.h>


struct Rect
{
    union
    {
        struct
        {
            float x;
            float y;
            float width;
            float height;
        };
    };


    inline Rect(float r, float y, float width, float height);

};

Rect::Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
