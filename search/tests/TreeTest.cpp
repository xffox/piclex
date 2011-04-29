#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Tree.h"

using namespace search;

class TreeTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TreeTest);
    CPPUNIT_TEST(testInsert1);
    CPPUNIT_TEST(testInsert2);
    CPPUNIT_TEST(testAppend1);
    CPPUNIT_TEST(testInsertChildsParent1);
    CPPUNIT_TEST(testInsertChildsErase1);
    CPPUNIT_TEST_SUITE_END();

public:
    void testInsert1()
    {
        Tree<int> tree;

        {
            Tree<int>::Iterator iter = tree.root();
            CPPUNIT_ASSERT(iter.isEnd());
            tree.insert(iter, 42);
        }

        Tree<int>::Iterator iter = tree.root();

        CPPUNIT_ASSERT(*iter == 42);
        iter.down(0);
        CPPUNIT_ASSERT(iter.isEnd());
    }

    void testInsert2()
    {
        Tree<int> tree;

        {
            Tree<int>::Iterator iter = tree.root();
            CPPUNIT_ASSERT(iter.isEnd());
            tree.insert(iter, 42);
            tree.insert(iter, 43);
        }

        Tree<int>::Iterator iter = tree.root();

        CPPUNIT_ASSERT(*iter == 42);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 43);
        iter.down(0);
        CPPUNIT_ASSERT(iter.isEnd());
    }

    void testAppend1()
    {
        Tree<int> tree;

        {
            Tree<int>::Iterator iter = tree.root();
            CPPUNIT_ASSERT(iter.isEnd());
            tree.insert(iter, 42);
            iter.up();
            tree.appendChild(iter, 43);
            tree.appendChild(iter, 44);

        }

        Tree<int>::Iterator iter = tree.root();
        CPPUNIT_ASSERT(*iter == 42);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 43);
        iter.up();
        iter.down(1);
        CPPUNIT_ASSERT(*iter == 44);
        iter.down(0);
        CPPUNIT_ASSERT(iter.isEnd());
    }

    void testInsertChildsParent1()
    {
        Tree<int> tree;

        {
            Tree<int>::Iterator iter = tree.root();
            CPPUNIT_ASSERT(iter.isEnd());
            tree.insert(iter, 42);
            iter.up();
            tree.appendChild(iter, 43);
            tree.appendChild(iter, 44);
            tree.insertChildsParent(iter, 45, 0, 2);
        }

        Tree<int>::Iterator iter = tree.root();
        CPPUNIT_ASSERT(*iter == 42);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 45);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 43);
        iter.up();
        iter.down(1);
        CPPUNIT_ASSERT(*iter == 44);
        iter.down(0);
        CPPUNIT_ASSERT(iter.isEnd());
    }

    void testInsertChildsErase1()
    {
        Tree<int> tree;

        {
            Tree<int>::Iterator iter = tree.root();
            CPPUNIT_ASSERT(iter.isEnd());
            tree.insert(iter, 42);
            iter.up();
            tree.appendChild(iter, 43);
            tree.appendChild(iter, 44);
            tree.insertChildsParent(iter, 45, 0, 2);
        }

        Tree<int>::Iterator iter = tree.root();
        CPPUNIT_ASSERT(*iter == 42);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 45);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 43);
        iter.up();
        iter.down(1);
        CPPUNIT_ASSERT(*iter == 44);
        tree.erase(iter);
        CPPUNIT_ASSERT(*iter == 45);
        CPPUNIT_ASSERT(iter.getChildsCount() == 1);
        iter.down(0);
        CPPUNIT_ASSERT(*iter == 43);
        tree.erase(iter);
        CPPUNIT_ASSERT(*iter == 45);
        CPPUNIT_ASSERT(iter.getChildsCount() == 0);
        tree.erase(iter);
        CPPUNIT_ASSERT(*iter == 42);
        CPPUNIT_ASSERT(iter.getChildsCount() == 0);
        tree.erase(iter);
        CPPUNIT_ASSERT(iter.isEnd());
        CPPUNIT_ASSERT(tree.root().isEnd());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TreeTest);
