#include "IndexMakerFactory.h"

#include "IndexMaker.h"
#include "mock/SimpleIndexMaker.h"

namespace search
{
IndexMaker *createIndexMaker(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor)
{
    return new SimpleIndexMaker(docIdReader, docProcessor);
}

}
