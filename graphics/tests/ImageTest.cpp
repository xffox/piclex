#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Image.h"

using namespace graphics;

class ImageTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ImageTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST_SUITE_END();

public:
    void test1()
    {
        Image a;
        Image b;

        a = b;

        CPPUNIT_ASSERT(a == b);
    }

    void test2()
    {
        Image a(100, 100);
        Image b(100, 100);

        a = b;

        CPPUNIT_ASSERT(a == b);
    }

    void test3()
    {
        Image a(100, 100);
        Image b(100, 100);

        a = b;

        a.set(99, 99, pixel(1,1,1));

        CPPUNIT_ASSERT(!(a == b));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
