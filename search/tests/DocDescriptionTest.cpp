#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "DocDescription.h"

using namespace search;

class DocDescriptionTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(DocDescriptionTest);
    CPPUNIT_TEST(testAddObject);
    CPPUNIT_TEST(testAddRelation);
    CPPUNIT_TEST_SUITE_END();

public:
    void testAddObject()
    {
        DocDescription descr;

        const DescriptionObject object = "circle";

        CPPUNIT_ASSERT(descr.isObject(object) == false);

        descr.addObject(object);
        CPPUNIT_ASSERT(descr.isObject(object) == true);
    }

    void testAddRelation()
    {
        DocDescription descr;

        const DescriptionObject firstObject = "circle";
        const DescriptionObject secondObject = "square";
        const DescriptionRelation relation = "left";

        CPPUNIT_ASSERT(descr.isObject(firstObject) == false);
        CPPUNIT_ASSERT(descr.isObject(firstObject) == false);
        CPPUNIT_ASSERT(descr.isObjectsRelation(firstObject, secondObject,
                    relation) == false);

        descr.addRelation(firstObject, secondObject, relation);
        CPPUNIT_ASSERT(descr.isObject(firstObject) == true);
        CPPUNIT_ASSERT(descr.isObject(secondObject) == true);
        CPPUNIT_ASSERT(descr.isObjectsRelation(firstObject, secondObject,
                    relation) == true);

        CPPUNIT_ASSERT(descr.isObjectsRelation(secondObject, firstObject,
                    relation) == false);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(DocDescriptionTest);
