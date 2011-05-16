#ifndef ID_STORAGE_H
#define ID_STORAGE_H

#include <vector>
#include <string>
#include <cassert>

#include "BaseExceptions.h"
#include "Nullable.h"

namespace search
{
typedef size_t StorageId;

//! The class is used to generate and store IDs.
/*!
 * Key-value storage. Whenever an ID for an unknown value is retreived a new
 * ID is generated and associated with this value.
 */
template<class ValueType>
class IdStorage
{
public:
    typedef ValueType Value;

private:
    typedef std::vector<base::Nullable<ValueType> > IdCollection;

public:
    //! Retreive an ID.
    /*! 
     * An existing ID is returned for a known value. A new ID is generated
     * for an unknown value.
     */
    StorageId getId(const ValueType &value);

    //! Retreive an ID.
    /*!
     * An existing ID is returned for a known value.
     * \exception base::NotFoundError unknown value.
     */
    StorageId getExistingId(const ValueType &value) const;

    //! Retreive a value.
    const ValueType &getValue(StorageId id) const;

    //! Retreive a value.
    const ValueType &operator[](StorageId id) const;

    //! Clear the storage.
    void clear();
    
    //! Remove an ID and an associated value by the id.
    void removeId(StorageId id); 

    //! Remove an ID and an associated value by the value.
    void removeValue(const ValueType &value);

    //! Get IDs internal storage size.
    /*!
     * Used for debugging purposes.
     */
    size_t getAllocatedIdsSize() const;

    //! Get all values.
    void getValues(std::vector<ValueType> &values) const;

private:
    void shrink();

private:
    IdCollection mIds;
};

class IdStorageInternalError: public base::BaseException
{
};

template<class ValueType>
StorageId IdStorage<ValueType>::getId( const ValueType &value)
{
    StorageId firstEmptyId = mIds.size();
    typename IdCollection::const_iterator iter = mIds.begin();
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
        mIds.push_back(base::Nullable<ValueType>(value));
    else
        mIds[firstEmptyId] = base::Nullable<ValueType>(value);
    return firstEmptyId;
}

template<class ValueType>
StorageId IdStorage<ValueType>::getExistingId( const ValueType &value
        ) const
{
    typename IdCollection::const_iterator iter = mIds.begin();
    for(; iter != mIds.end(); ++iter)
        if(!iter->isNull() && iter->getValue() == value)
            return iter - mIds.begin();
    throw base::NotFoundError();
}

template<class ValueType>
const ValueType &IdStorage<ValueType>::getValue(StorageId id) const
{
    if(id < mIds.size() && !mIds[id].isNull())
        return mIds[id].getValue();
    throw base::NotFoundError();
}

template<class ValueType>
const ValueType &IdStorage<ValueType>::operator[](StorageId id) const
{
    return getValue(id);
}

template<class ValueType>
void IdStorage<ValueType>::clear()
{
    mIds.clear();
}

template<class ValueType>
void IdStorage<ValueType>::removeValue(const ValueType &value)
{
    StorageId id = mIds.size();
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

template<class ValueType>
void IdStorage<ValueType>::removeId(StorageId id)
{
    if(id < mIds.size() && !mIds[id].isNull())
    {
        mIds[id] = base::Nullable<ValueType>();

        shrink();
    }
    else
    {
        throw base::NotFoundError();
    }
}

template<class ValueType>
size_t IdStorage<ValueType>::getAllocatedIdsSize() const
{
    return mIds.size();
}

template<class ValueType>
void IdStorage<ValueType>::getValues(std::vector<ValueType> &values) const
{
    values.clear();

    typename IdCollection::const_iterator iter = mIds.begin();
    for(; iter != mIds.end(); ++iter)
        if(!iter->isNull())
            values.push_back(iter->getValue());
}

template<class ValueType>
void IdStorage<ValueType>::shrink()
{
    StorageId id = mIds.size();
    for(; id > 0 && mIds[id-1].isNull(); --id)
        ;
    mIds.erase(mIds.begin() + id, mIds.end());
}

}

#endif//ID_STORAGE_H
