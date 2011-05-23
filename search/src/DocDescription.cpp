#include "DocDescription.h"

namespace search
{
DocDescription::~DocDescription()
{
}

void DocDescription::addObject(const DescriptionObject &object)
{
    getNewObjectIndex(object);

    processAddObject(object);
}

void DocDescription::addRelation(const DescriptionObject &firstObject,
        const DescriptionObject &secondObject,
        const DescriptionRelation &relation)
{
    size_t firstObjectIndex = getNewObjectIndex(firstObject);
    size_t secondObjectIndex = getNewObjectIndex(secondObject);
    size_t relationIndex = getNewRelationIndex(relation);

    try
    {
        mObjectsRelations.set(relationIndex, firstObjectIndex,
                secondObjectIndex, true);
    }
    catch(base::OutOfBoundError &exc)
    {
        throw DocDescriptionInternalError();
    }

    processAddRelation(firstObject, secondObject, relation);
}

bool DocDescription::operator==(const DocDescription &that) const
{
    if(mObjects.size() != that.mObjects.size() ||
            mRelations.size() != that.mRelations.size())
        return false;

    return isSubsetEq(that);
}

bool DocDescription::isSubsetEq(const DocDescription &that) const
{
    if(mObjects.size() > that.mObjects.size() ||
            mRelations.size() > that.mRelations.size())
        return false;

    Objects::const_iterator objectIter = mObjects.begin();
    Relations::const_iterator relationIter;
    size_t thisObjectIndex = 0;
    size_t thisRelationIndex = 0;
    size_t thatObjectIndex = 0;
    size_t thatRelationIndex = 0;
    //FIXME
    for(; objectIter != mObjects.end(); ++objectIter)
    {
        thatObjectIndex = that.getObjectIndex(*objectIter);
        if(thatObjectIndex == that.mObjects.size())
            return false;

        thisObjectIndex = objectIter - mObjects.begin();

        for(relationIter = mRelations.begin();
                relationIter != mRelations.end(); ++relationIter)
        {
            thatRelationIndex = that.getRelationIndex(*relationIter);
            if(thatRelationIndex == that.mRelations.size())
                return false;

            thisRelationIndex = relationIter - mRelations.begin();

            if(mObjectsRelations.get(thisRelationIndex, thisObjectIndex,
                        thisObjectIndex) !=
                    that.mObjectsRelations.get(thatRelationIndex,
                        thatObjectIndex, thatObjectIndex))
                return false;
        }
    }
    return true;
}

bool DocDescription::isObject(const DescriptionObject &object) const
{
    return getObjectIndex(object) != mObjects.size();
}

bool DocDescription::isObjectsRelation(const DescriptionObject &firstObject,
        const DescriptionObject &secondObject,
        const DescriptionRelation &relation) const
{
    size_t firstObjectIndex = getObjectIndex(firstObject);
    if(firstObjectIndex == mObjects.size())
        return false;

    size_t secondObjectIndex = getObjectIndex(secondObject);
    if(secondObjectIndex == mObjects.size())
        return false;

    size_t relationIndex = getRelationIndex(relation);
    if(relationIndex == mRelations.size())
        return false;

    return mObjectsRelations.get(relationIndex, firstObjectIndex,
            secondObjectIndex);
}

void DocDescription::processAddObject(const DescriptionObject&) const
{
}

void DocDescription::processAddRelation(const DescriptionObject&,
        const DescriptionObject&, const DescriptionRelation&) const
{
}

size_t DocDescription::getObjectIndex(const DescriptionObject &object) const
{
    Objects::const_iterator objectIter = mObjects.begin();
    for(; objectIter != mObjects.end(); ++objectIter)
        if(*objectIter == object)
            return objectIter - mObjects.begin();
    return mObjects.size();
}

size_t DocDescription::getRelationIndex(const DescriptionRelation &relation
        ) const
{
    Relations::const_iterator relationIter = mRelations.begin();
    for(; relationIter != mRelations.end(); ++relationIter)
        if(*relationIter == relation)
            return relationIter - mRelations.begin();
    return mRelations.size();
}

size_t DocDescription::getNewObjectIndex(const DescriptionObject &object)
{
    size_t index = getObjectIndex(object);
    if(index == mObjects.size())
    {
        if(mObjectsRelations.getPages() != mRelations.size() ||
                mObjectsRelations.getRows() != mObjects.size() ||
                mObjectsRelations.getColumns() != mObjects.size())
            throw DocDescriptionInternalError();

        mObjects.push_back(object);
        
        mObjectsRelations.resize(mRelations.size(), mObjects.size(),
                mObjects.size(), false);
    }

    return index;
}

size_t DocDescription::getNewRelationIndex(const DescriptionRelation &relation)
{
    size_t index = getRelationIndex(relation);
    if(index == mRelations.size())
    {
        if(mObjectsRelations.getPages() != mRelations.size() ||
                mObjectsRelations.getRows() != mObjects.size() ||
                mObjectsRelations.getColumns() != mObjects.size())
            throw DocDescriptionInternalError();

        mRelations.push_back(relation);

        mObjectsRelations.resize(mRelations.size(), mObjects.size(),
                mObjects.size(), false);
    }

    return index;
}

}
