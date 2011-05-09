#ifndef ID_STORAGE_H
#define ID_STORAGE_H

#include <vector>

#include "SearchDefines.h"
#include "BaseExceptions.h"
#include "Nullable.h"

//TODO: make a template out of that
namespace search
{
//! The class is used to generate and store IDs.
/*!
 * Key-value storage. Whenever an ID for an unknown value is retreived a new
 * ID is generated and associated with this value.
 */
class IdStorage
{
    typedef std::vector<base::Nullable<Term> > IdCollection;

public:
    //! Retreive an ID.
    /*! 
     * An existing ID is returned for a known value. A new ID is generated
     * for an unknown value.
     */
    Id getId(const Term &value);

    //! Retreive an ID.
    /*!
     * An existing ID is returned for a known value.
     * \exception base::NotFoundError unknown value.
     */
    Id getExistingId(const Term &value) const;

    //! Retreive a value.
    const Term &getValue(Id id) const;

    //! Retreive a value.
    const Term &operator[](Id id) const;

    //! Clear the storage.
    void clear();
    
    //! Remove an ID and an associated value by the id.
    void removeId(Id id); 

    //! Remove an ID and an associated value by the value.
    void removeValue(const Term &value);

    //! Get IDs internal storage size.
    /*!
     * Used for debugging purposes.
     */
    size_t getAllocatedIdsSize() const;

private:
    void shrink();

private:
    IdCollection mIds;
};

class IdStorageInternalError: public base::BaseException
{
};

}

#endif//ID_STORAGE_H
