#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Symbol.h"

using namespace search;

class SymbolTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SymbolTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(testCharConstructor);
    CPPUNIT_TEST(testComparison1);
    CPPUNIT_TEST(testComparison2);
    CPPUNIT_TEST(testComparison3);
    CPPUNIT_TEST(testComparison4);
    CPPUNIT_TEST_SUITE_END();

public:
    void test1()
    {
        Symbol a(NONTERMINAL, 42);

        CPPUNIT_ASSERT(a.getType() == NONTERMINAL);
        CPPUNIT_ASSERT(a.getValue() == 42);
    }

    void testCharConstructor()
    {
        Symbol a('x');

        CPPUNIT_ASSERT(a.getType() == TERMINAL);
        CPPUNIT_ASSERT(a.getValue() == 'x');
    }

    void testComparison1()
    {
        Symbol a(TERMINAL, 42);
        Symbol b(TERMINAL, 42);

        CPPUNIT_ASSERT(a == b);
    }

    void testComparison2()
    {
        Symbol a(TERMINAL, 41);
        Symbol b(TERMINAL, 42);

        CPPUNIT_ASSERT(a != b);
    }

    void testComparison3()
    {
        Symbol a(TERMINAL, 42);
        Symbol b(NONTERMINAL, 42);

        CPPUNIT_ASSERT(a != b);
    }

    void testComparison4()
    {
        Symbol a(TERMINAL, 41);
        Symbol b(NONTERMINAL, 42);

        CPPUNIT_ASSERT(a != b);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SymbolTest);
