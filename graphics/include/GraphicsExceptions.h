#ifndef GRAPHICS_EXCEPTIONS_H
#define GRAPHICS_EXCEPTIONS_H

#include "Image.h"

namespace graphics
{
class OutOfBoundError
{
public:
    OutOfBoundError(Coordinate x, Coordinate y,
            Coordinate width, Coordinate height)
        :mX(x), mY(y), mWidth(width), mHeight(height)
    {
    }

    Coordinate getX() const
    {
        return mX;
    }

    Coordinate getY() const
    {
        return mY;
    }

    Coordinate getWidth() const
    {
        return mWidth;
    }

    Coordinate getHeight() const
    {
        return mHeight;
    }

private:
    Coordinate mX;
    Coordinate mY;
    Coordinate mWidth;
    Coordinate mHeight;
};

class InternalError
{
    InternalError()
    {
    }
};
}

#endif//GRAPHICS_EXCEPTIONS_H
