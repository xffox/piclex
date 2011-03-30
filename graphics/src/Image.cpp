#include "Image.h"

#include <cstring>

#include "GraphicsExceptions.h"

namespace graphics
{

Image::Image():mWidth(0), mHeight(0), mData(NULL), mDataSize(0)
{

}

Image::Image(Coordinate width, Coordinate height)
    :mWidth(width), mHeight(height), mData(NULL), mDataSize(0)
{
    allocateData(mWidth, mHeight);

    memset(mData, 0, sizeof(Pixel)*mWidth*mHeight);
}

Image::~Image()
{
    delete[] mData;
}

Image::Image(const Image &that)
    :mWidth(that.mWidth), mHeight(that.mHeight), mData(NULL), mDataSize(0)
{
    allocateData(mWidth, mHeight);

    memcpy(mData, that.mData, sizeof(Pixel)*mWidth*mHeight);
}

Image &Image::operator=(const Image &that)
{
    mWidth = that.mWidth;
    mHeight = that.mHeight;

    reallocateData(mWidth, mHeight);

    memcpy(mData, that.mData, sizeof(Pixel)*mWidth*mHeight);

    return *this;
}

bool Image::operator==(const Image &that) const
{
    if(mWidth != that.mWidth || mHeight != that.mHeight)
        return false;

    if(mWidth > 0 || mHeight > 0)
        return !memcmp(mData, that.mData, sizeof(Pixel)*mWidth*mHeight);
    return true;
}

Pixel Image::get(Coordinate x, Coordinate y) const
{
    if(x >= mWidth || y >= mHeight)
        throw OutOfBoundError(x, y, mWidth, mHeight);
    return mData[mWidth*y + x];
}

void Image::set(Coordinate x, Coordinate y, Pixel pl)
{
    if(x >= mWidth || y >= mHeight)
        throw OutOfBoundError(x, y, mWidth, mHeight);
    mData[mWidth*y + x] = pl;
}

Coordinate Image::getWidth() const
{
    return mWidth;
}

Coordinate Image::getHeight() const
{
    return mHeight;
}

void Image::allocateData(Coordinate width, Coordinate height)
{
    size_t newDataSize = width*height;
    if(newDataSize > 0)
        mData = new Pixel[newDataSize];
    else
        mData = NULL;
    mDataSize = newDataSize;
}

void Image::reallocateData(Coordinate width, Coordinate height)
{
    size_t newDataSize = width*height;
    if(mDataSize < newDataSize)
    {
        delete[] mData;
        mData = NULL;
        mData = new Pixel[newDataSize];
        mDataSize = newDataSize;
    }
}

const size_t RED_OFFSET = 0;
const size_t GREEN_OFFSET = 1;
const size_t BLUE_OFFSET = 2;

Color red(Pixel pl)
{
    uint8_t *colorArray = reinterpret_cast<uint8_t *>(&pl);
    return colorArray[RED_OFFSET];
}

Color green(Pixel pl)
{
    uint8_t *colorArray = reinterpret_cast<uint8_t *>(&pl);
    return colorArray[GREEN_OFFSET];
}

Color blue(Pixel pl)
{
    uint8_t *colorArray = reinterpret_cast<uint8_t *>(&pl);
    return colorArray[BLUE_OFFSET];
}

Pixel pixel(Color red, Color green, Color blue)
{
    Pixel pl = 0;
    uint8_t *colorArray = reinterpret_cast<uint8_t *>(&pl);

    colorArray[RED_OFFSET] = red;
    colorArray[GREEN_OFFSET] = green;
    colorArray[BLUE_OFFSET] = blue;

    return pl;
}

}
