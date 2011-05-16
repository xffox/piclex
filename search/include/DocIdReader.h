#ifndef DOC_ID_READER_H
#define DOC_ID_READER_H

#include "SearchDefines.h"
#include "BaseExceptions.h"

namespace search
{
class DocProvider;

class DocIdReaderInternalError: public base::BaseException
{
};

//! A wrapper on DocProvider to access documents by DocId.
class DocIdReader
{
public:
    DocIdReader(const DocProvider *docProvider, const DocIdStorage *idStorage);
    ~DocIdReader();

    void read(Document &document, DocId id) const;

private:
    const DocProvider *mDocProvider;

    const DocIdStorage *mIdStorage;
};

}

#endif//DOC_ID_READER_H
