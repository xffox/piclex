#ifndef SIMPLE_INDEX_MAKER_H
#define SIMPLE_INDEX_MAKER_H

#include "BaseExceptions.h"
#include "IndexMaker.h"

namespace search
{
class SimpleIndexMakerInternalError: public base::BaseException
{
};

class SimpleIndexMaker: public IndexMaker
{
public:
    SimpleIndexMaker(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor);
    virtual ~SimpleIndexMaker();

    virtual void tokenize(std::vector<IndexToken> &tokens,
            const std::vector<DocId> &docIds);
    virtual void makeIndex(InvertedIndex &index,
            const std::vector<IndexToken> &tokens);
};

}

#endif//SIMPLE_INDEX_MAKER_H
