#include "IndexSearcherFactory.h"

#include "IndexSearcher.h"
#include "mock/SimpleIndexSearcher.h"

namespace search
{
IndexSearcher *createIndexSearcher(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor,
            const DocProcessor *queryProcessor)
{
    return new SimpleIndexSearcher(docIdReader, docProcessor, queryProcessor);
}

}
