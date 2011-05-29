#ifndef DOC_PROCESSOR_H
#define DOC_PROCESSOR_H

#include <set>

#include "Clonable.h"
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

class DocDescription;

class DocProcessor: public base::Clonable<DocProcessor>
{
public:
    virtual ~DocProcessor(){};

    //! Prototype pattern method.
    /*!
     * Override in subclasses.
     */
    virtual DocProcessor *clone() const = 0;

    //! Set document content.
    virtual bool setDocument(const Document &document) = 0;

    //! Get terms from the processed document.
    virtual void getTerms(std::set<Term> &terms) const = 0;

    //! Get document description.
    /*!
     * Can return NULL.
     */
    virtual const DocDescription *getDocDescription() const = 0;
};

}

#endif//DOC_PROCESSOR_H
