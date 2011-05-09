#include "IdStorage.h"

#include <cassert>

namespace search
{
Id IdStorage::getId(const Term &value)
{
    Id firstEmptyId = mIds.size();
    IdCollection::const_iterator iter = mIds.begin();
    for(; iter != mIds.end(); ++iter)
        if(!iter->isNull())
        {
            if(iter->getValue() == value)
                return iter - mIds.begin();
        }
        else
        {
            if(firstEmptyId == mIds.size())
                firstEmptyId = iter - mIds.begin();
        }

    assert(firstEmptyId <= mIds.size());
    if(firstEmptyId == mIds.size())
        mIds.push_back(base::Nullable<Term>(value));
    else
        mIds[firstEmptyId] = base::Nullable<Term>(value);
    return firstEmptyId;
}

Id IdStorage::getExistingId(const Term &value) const
{
    IdCollection::const_iterator iter = mIds.begin();
    for(; iter != mIds.end(); ++iter)
        if(!iter->isNull() && iter->getValue() == value)
            return iter - mIds.begin();
    throw base::NotFoundError();
}

const Term &IdStorage::getValue(Id id) const
{
    if(id < mIds.size() && !mIds[id].isNull())
        return mIds[id].getValue();
    throw base::NotFoundError();
}

const Term &IdStorage::operator[](Id id) const
{
    return getValue(id);
}

void IdStorage::clear()
{
    mIds.clear();
}

void IdStorage::removeValue(const Term &value)
{
    Id id = mIds.size();
    try
    {
        id = getExistingId(value);
    }
    catch(base::NotFoundError &exc)
    {
        throw;
    }

    try
    {
        removeId(id);
    }
    catch(base::NotFoundError &exc)
    {
        throw IdStorageInternalError();
    }
}

void IdStorage::removeId(Id id)
{
    if(id < mIds.size() && !mIds[id].isNull())
    {
        mIds[id] = base::Nullable<Term>();

        shrink();
    }
    else
    {
        throw base::NotFoundError();
    }
}

size_t IdStorage::getAllocatedIdsSize() const
{
    return mIds.size();
}

void IdStorage::shrink()
{
    Id id = mIds.size();
    for(; id > 0 && mIds[id-1].isNull(); --id)
        ;
    mIds.erase(mIds.begin() + id, mIds.end());
}

}
