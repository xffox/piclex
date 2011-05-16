#include "IndexMaker.h"

#include "BaseExceptions.h"
#include "DocIdReader.h"
#include "IndexToken.h"

namespace search
{
IndexMaker::IndexMaker(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor)
    :mDocIdReader(docIdReader), mDocProcessor(docProcessor)
{
    if(!docIdReader || !docProcessor)
        throw base::InvalidArgument();
}

IndexMaker::~IndexMaker()
{
}

const InvertedIndex &IndexMaker::getIndex() const
{
    return mIndex;
}

void IndexMaker::index(const std::vector<DocId> &docIds)
{
    std::vector<IndexToken> tokens;

    tokenize(tokens, docIds);

    // TODO: probably need to clear
    makeIndex(mIndex, tokens);
}

const DocIdReader *IndexMaker::getDocIdReader() const
{
    return mDocIdReader;
}

const DocProcessor *IndexMaker::getDocProcessor() const
{
    return mDocProcessor;
}

}
