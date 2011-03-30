#include <stdint.h>
#include <cstddef>

namespace graphics
{
typedef uint32_t Pixel;
typedef uint8_t Color;
typedef unsigned int Coordinate;

class Image
{
public:
    Image();
    Image(Coordinate width, Coordinate height);
    virtual ~Image();
    Image(const Image &that);

    Image &operator=(const Image &that);

    bool operator==(const Image &that) const;

    virtual Pixel get(Coordinate x, Coordinate y) const;
    virtual void set(Coordinate x, Coordinate y, Pixel pl);

    virtual Coordinate getWidth() const;
    virtual Coordinate getHeight() const;

private:
    void allocateData(Coordinate width, Coordinate height);
    void reallocateData(Coordinate width, Coordinate height);

    Coordinate mWidth;
    Coordinate mHeight;

    Pixel *mData;
    size_t mDataSize;
};

Color red(Pixel pl);
Color green(Pixel pl);
Color blue(Pixel pl);

Pixel pixel(Color red, Color green, Color blue);
}
