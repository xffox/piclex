#include "DocIdReader.h"

#include "DocProvider.h"

namespace search
{
DocIdReader::DocIdReader(const DocProvider *docProvider,
        const DocIdStorage *idStorage)
    :mDocProvider(docProvider), mIdStorage(idStorage)
{
    if(!docProvider || !idStorage)
        throw base::InvalidArgument();
}

DocIdReader::~DocIdReader()
{
}

void DocIdReader::read(Document &document, DocId id) const
{
    if(!mDocProvider || !mIdStorage)
        throw DocIdReaderInternalError();

    std::string name;
    try
    {
        name = mIdStorage->getValue(id);
    }
    catch(base::NotFoundError &exc)
    {
        throw;
    }

    mDocProvider->read(document, name);
}
}
