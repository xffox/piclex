#ifndef DOC_PROCESSOR_H
#define DOC_PROCESSOR_H

#include <set>

#include "BaseExceptions.h"
#include "SearchDefines.h"

namespace search
{
//! Document content processor.
/*!
 * Prototype pattern used.
 */
class DocProcessError: public base::BaseException
{
};

class DocProcessor
{
public:
    virtual ~DocProcessor(){};

    //! Prototype pattern method.
    /*!
     * Override in subclasses.
     */
    virtual DocProcessor *clone() const = 0;

    //! Set document content.
    virtual void setDocument(const Document &document) = 0;

    //! Get terms from the processed document.
    virtual void getTerms(std::set<Term> &terms) const = 0;
};

}

#endif//DOC_PROCESSOR_H
