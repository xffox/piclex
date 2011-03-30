#include <iostream>

#include "Image.h"

using namespace graphics;


namespace
{
void printPixel(Pixel pl)
{
    std::cout<<"("<<static_cast<unsigned int>(red(pl))
        <<", "<<static_cast<unsigned int>(green(pl))
        <<", "<<static_cast<unsigned int>(blue(pl))<<")";
}
}

int main()
{
    Image a(100, 200);
    Image b(a);
    Image c;
    c = a;

    std::cout<<"("<<c.getWidth()<<","<<c.getHeight()<<")"<<std::endl;

    c.set(99, 199, pixel(42, 43, 44));

    Pixel p = c.get(99, 199);

    b = c;

    printPixel(b.get(98, 198));
    std::cout<<std::endl;
    printPixel(b.get(98, 199));
    std::cout<<std::endl;
    printPixel(b.get(99, 198));
    std::cout<<std::endl;
    printPixel(b.get(99, 199));
    std::cout<<std::endl;

    return 0;
}
