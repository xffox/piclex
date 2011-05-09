#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "IdStorage.h"

using namespace base;
using namespace search;

class IdStorageTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(IdStorageTest);
    CPPUNIT_TEST(testGetId);
    CPPUNIT_TEST(testGetExistingId);
    CPPUNIT_TEST(testGetValue);
    CPPUNIT_TEST(testRemoveId);
    CPPUNIT_TEST(testRemoveValue);
    CPPUNIT_TEST_EXCEPTION(testValueNotFoundError, NotFoundError);
    CPPUNIT_TEST_EXCEPTION(testIdNotFoundError, NotFoundError);
    CPPUNIT_TEST_EXCEPTION(testOperatorIdNotFoundError, NotFoundError);
    CPPUNIT_TEST_EXCEPTION(testRemoveIdNotFoundError, NotFoundError);
    CPPUNIT_TEST_EXCEPTION(testRemoveValueNotFoundError, NotFoundError);
    CPPUNIT_TEST_SUITE_END();

public:
    void testGetId()
    {
        IdStorage idStorage;

        const Term value1("foo");
        Id id1 = idStorage.getId(value1);

        CPPUNIT_ASSERT(idStorage.getId(value1) == id1);

        const Term value2("bar");
        Id id2 = idStorage.getId(value2);

        CPPUNIT_ASSERT(idStorage.getId(value1) == id1);
        CPPUNIT_ASSERT(idStorage.getId(value2) == id2);
    }

    void testGetExistingId()
    {
        IdStorage idStorage;

        const Term value1("foo");
        Id id1 = idStorage.getId(value1);

        CPPUNIT_ASSERT(idStorage.getExistingId(value1) == id1);

        const Term value2("bar");
        Id id2 = idStorage.getId(value2);

        CPPUNIT_ASSERT(idStorage.getExistingId(value1) == id1);
        CPPUNIT_ASSERT(idStorage.getExistingId(value2) == id2);
    }

    void testGetValue()
    {
        IdStorage idStorage;

        const Term value1("foo");
        Id id1 = idStorage.getId(value1);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);

        const Term value2("bar");
        Id id2 = idStorage.getId(value2);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);
        CPPUNIT_ASSERT(idStorage.getValue(id2) == value2);
    }

    void testRemoveId()
    {
        IdStorage idStorage;

        const Term value1("foo");
        Id id1 = idStorage.getId(value1);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);

        const Term value2("bar");
        Id id2 = idStorage.getId(value2);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);
        CPPUNIT_ASSERT(idStorage.getValue(id2) == value2);

        bool notFound = false;
        idStorage.removeId(id1);
        try
        {
            idStorage.getValue(id1);
        }
        catch(base::NotFoundError &exc)
        {
            notFound = true;
        }
        CPPUNIT_ASSERT(notFound);
        CPPUNIT_ASSERT(idStorage.getValue(id2) == value2);
        CPPUNIT_ASSERT(idStorage.getAllocatedIdsSize() == 2);

        notFound = false;
        idStorage.removeId(id2);
        try
        {
            idStorage.getValue(id2);
        }
        catch(base::NotFoundError &exc)
        {
            notFound = true;
        }
        CPPUNIT_ASSERT(notFound);
        CPPUNIT_ASSERT(idStorage.getAllocatedIdsSize() == 0);
    }

    void testRemoveValue()
    { 
        IdStorage idStorage;

        const Term value1("foo");
        Id id1 = idStorage.getId(value1);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);

        const Term value2("bar");
        Id id2 = idStorage.getId(value2);

        CPPUNIT_ASSERT(idStorage.getValue(id1) == value1);
        CPPUNIT_ASSERT(idStorage.getValue(id2) == value2);

        bool notFound = false;
        idStorage.removeValue(value1);
        try
        {
            idStorage.getValue(id1);
        }
        catch(base::NotFoundError &exc)
        {
            notFound = true;
        }
        CPPUNIT_ASSERT(notFound);
        CPPUNIT_ASSERT(idStorage.getValue(id2) == value2);
        CPPUNIT_ASSERT(idStorage.getAllocatedIdsSize() == 2);

        notFound = false;
        idStorage.removeValue(value2);
        try
        {
            idStorage.getValue(id2);
        }
        catch(base::NotFoundError &exc)
        {
            notFound = true;
        }
        CPPUNIT_ASSERT(notFound);
        CPPUNIT_ASSERT(idStorage.getAllocatedIdsSize() == 0);
    }

    void testValueNotFoundError()
    {
        IdStorage idStorage;

        idStorage.getExistingId("foobar");
    }

    void testIdNotFoundError()
    {
        IdStorage idStorage;

        Term value = idStorage.getValue(0);
    }

    void testOperatorIdNotFoundError()
    {
        IdStorage idStorage;

        Term value = idStorage[0];
    }

    void testRemoveIdNotFoundError()
    {
        IdStorage idStorage;

        idStorage.removeId(0);
    }

    void testRemoveValueNotFoundError()
    {
        IdStorage idStorage;

        idStorage.removeValue("foobar");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(IdStorageTest);
