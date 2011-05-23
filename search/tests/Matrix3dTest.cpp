#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Matrix3d.h"

using namespace search;
using namespace base;

class Matrix3dTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Matrix3dTest);
    CPPUNIT_TEST(testDefaultCreate);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testResize1);
    CPPUNIT_TEST(testResize2);
    CPPUNIT_TEST(testResize3);
    CPPUNIT_TEST(testResize4);
    CPPUNIT_TEST_EXCEPTION(testOutOfBoundError, OutOfBoundError);
    CPPUNIT_TEST_SUITE_END();

public:
    void testDefaultCreate()
    {
        Matrix3d<int> m;

        CPPUNIT_ASSERT(m.getPages() == 0);
        CPPUNIT_ASSERT(m.getColumns() == 0);
        CPPUNIT_ASSERT(m.getRows() == 0);
    }

    void testCreate()
    {
        Matrix3d<int> m(41, 42, 43);

        CPPUNIT_ASSERT(m.getPages() == 41);
        CPPUNIT_ASSERT(m.getRows() == 42);
        CPPUNIT_ASSERT(m.getColumns() == 43);
    }

    void testGet()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<int> m(pages, rows, columns, 42);

        CPPUNIT_ASSERT(m.getPages() == pages);
        CPPUNIT_ASSERT(m.getRows() == rows);
        CPPUNIT_ASSERT(m.getColumns() == columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) == 42);
    }

    void testSet()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<unsigned int> m(pages, rows, columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    m.set(i, j, k, rows*columns * i + columns * j + k);

        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) ==
                            rows*columns * i + columns * j + k);
    }

    void testResize1()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<unsigned int> m(pages, rows, columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    m.set(i, j, k, rows*columns * i + columns * j + k);

        const size_t newPages = pages + 1;
        const size_t newRows = rows + 1;
        const size_t newColumns = columns + 1;
        const unsigned int val = 1000;
        m.resize(newPages, newRows, newColumns, val);

        CPPUNIT_ASSERT(m.getPages() == newPages);
        CPPUNIT_ASSERT(m.getRows() == newRows);
        CPPUNIT_ASSERT(m.getColumns() == newColumns);

        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) ==
                            ((i < pages && j < rows && k < columns)?
                            rows*columns * i + columns * j + k:val));
    }

    void testResize2()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<unsigned int> m(pages, rows, columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    m.set(i, j, k, rows*columns * i + columns * j + k);

        const size_t newPages = pages * 2;
        const size_t newRows = rows * 2;
        const size_t newColumns = columns * 2;
        const unsigned int val = 1000;
        m.resize(newPages, newRows, newColumns, val);

        CPPUNIT_ASSERT(m.getPages() == newPages);
        CPPUNIT_ASSERT(m.getRows() == newRows);
        CPPUNIT_ASSERT(m.getColumns() == newColumns);

        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) ==
                            ((i < pages && j < rows && k < columns)?
                            rows*columns * i + columns * j + k:val));
    }

    void testResize3()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<unsigned int> m(pages, rows, columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    m.set(i, j, k, rows*columns * i + columns * j + k);

        const size_t newPages = pages - 1;
        const size_t newRows = rows - 1;
        const size_t newColumns = columns - 1;
        const unsigned int val = 1000;
        m.resize(newPages, newRows, newColumns, val);

        CPPUNIT_ASSERT(m.getPages() == newPages);
        CPPUNIT_ASSERT(m.getRows() == newRows);
        CPPUNIT_ASSERT(m.getColumns() == newColumns);

        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) ==
                            ((i < pages && j < rows && k < columns)?
                            rows*columns * i + columns * j + k:val));
    }

    void testResize4()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<unsigned int> m(pages, rows, columns);

        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    m.set(i, j, k, rows*columns * i + columns * j + k);

        const size_t newPages = pages / 2;
        const size_t newRows = rows / 2;
        const size_t newColumns = columns / 2;
        const unsigned int val = 1000;
        m.resize(newPages, newRows, newColumns, val);

        CPPUNIT_ASSERT(m.getPages() == newPages);
        CPPUNIT_ASSERT(m.getRows() == newRows);
        CPPUNIT_ASSERT(m.getColumns() == newColumns);

        for(i = 0; i < m.getPages(); ++i)
            for(j = 0; j < m.getRows(); ++j)
                for(k = 0; k < m.getColumns(); ++k)
                    CPPUNIT_ASSERT(m.get(i, j, k) ==
                            ((i < pages && j < rows && k < columns)?
                            rows*columns * i + columns * j + k:val));
    }

    void testOutOfBoundError()
    {
        const size_t pages = 5;
        const size_t rows = 6;
        const size_t columns = 7;
        Matrix3d<int> m(pages, rows, columns);

        m.get(0, 0, columns);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(Matrix3dTest);
