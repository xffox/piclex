#include <iostream>

#include "Image.h"
#include "Logger.h"

using namespace graphics;
using namespace base;

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
    Log().setLogWriter( new TimestampedLogWriter(new FileLogWriter(
                    "tester.log")) );

    Image a(100, 200);
    Image b(a);
    Image c;
    c = a;

    Log().setSeverity(Logger::DEBUG);
    Log().debug("test %d", 1);
    Log().warning("test %d", 2);
    Log().error("test %s", "3");

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
