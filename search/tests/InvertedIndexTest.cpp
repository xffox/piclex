#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "InvertedIndex.h"

using namespace search;

class InvertedIndexTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(InvertedIndexTest);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testOrder);
    CPPUNIT_TEST_SUITE_END();

public:
    void testInsert()
    {
        InvertedIndex index;

        const Term term1("foo");
        index.insert(term1, 0);
        CPPUNIT_ASSERT(index.getPostings(term1).size() == 1);
        CPPUNIT_ASSERT(isContain(index.getPostings(term1), 0));

        index.insert(term1, 1);
        CPPUNIT_ASSERT(index.getPostings(term1).size() == 2);
        CPPUNIT_ASSERT(isContain(index.getPostings(term1), 0));
        CPPUNIT_ASSERT(isContain(index.getPostings(term1), 1));
        
        CPPUNIT_ASSERT(!isContain(index.getPostings(term1), 2));

        const Term term2("bar");
        index.insert(term2, 0);
        CPPUNIT_ASSERT(index.getPostings(term2).size() == 1);
        CPPUNIT_ASSERT(isContain(index.getPostings(term2), 0));

        index.insert(term2, 1);
        CPPUNIT_ASSERT(index.getPostings(term2).size() == 2);
        CPPUNIT_ASSERT(isContain(index.getPostings(term2), 0));
        CPPUNIT_ASSERT(isContain(index.getPostings(term2), 1));
        
        CPPUNIT_ASSERT(!isContain(index.getPostings(term2), 2));
    }

    void testOrder()
    {
        InvertedIndex index;

        const Term term1("foo");

        index.insert(term1, 0);
        index.insert(term1, 2);
        index.insert(term1, 1);
        index.insert(term1, 5);
        index.insert(term1, 4);
        index.insert(term1, 3);
        index.insert(term1, 6);

        const Postings &postings = index.getPostings(term1);

        CPPUNIT_ASSERT(postings.size() == 7);
        Postings::const_iterator iter = postings.begin();
        DocId prevId = *iter;
        ++iter;
        for(; iter != postings.end(); ++iter)
        {
            CPPUNIT_ASSERT(prevId < *iter);
            prevId = *iter;
        }
        CPPUNIT_ASSERT(prevId == 6);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(InvertedIndexTest);
