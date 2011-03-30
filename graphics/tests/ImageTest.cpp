#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Image.h"
#include "GraphicsExceptions.h"

using namespace graphics;

class ImageTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ImageTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);

    CPPUNIT_TEST_EXCEPTION(testSetOutOfBoundThrows1, OutOfBoundError);
    CPPUNIT_TEST_EXCEPTION(testSetOutOfBoundThrows2, OutOfBoundError);
    CPPUNIT_TEST_EXCEPTION(testSetOutOfBoundThrows3, OutOfBoundError);

    CPPUNIT_TEST_EXCEPTION(testSetBoundOutOfBoundThrows1, OutOfBoundError);
    CPPUNIT_TEST_EXCEPTION(testSetBoundOutOfBoundThrows2, OutOfBoundError);
    CPPUNIT_TEST_EXCEPTION(testSetBoundOutOfBoundThrows3, OutOfBoundError);

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

    void testSetOutOfBoundThrows1()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(11, 0, pl);
    }

    void testSetOutOfBoundThrows2()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(0, 11, pl);
    }

    void testSetOutOfBoundThrows3()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(11, 11, pl);
    }

    void testSetBoundOutOfBoundThrows1()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(10, 0, pl);
    }

    void testSetBoundOutOfBoundThrows2()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(0, 10, pl);
    }

    void testSetBoundOutOfBoundThrows3()
    {
        Image a(10, 10);

        Pixel pl = 0;
        a.set(10, 10, pl);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImageTest);
