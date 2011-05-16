#include "IndexSearcher.h"

#include "BaseExceptions.h"
#include "DocProcessor.h"

namespace search
{
IndexSearcher::IndexSearcher(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor,
            const DocProcessor *queryProcessor)
    :mDocIdReader(docIdReader), mDocProcessor(docProcessor)
    ,mQueryProcessor(queryProcessor)
{
    if(!docIdReader || !docProcessor || !queryProcessor)
        throw base::InvalidArgument();
}


IndexSearcher::~IndexSearcher()
{
}

void IndexSearcher::setIndex(const InvertedIndex &index)
{
    mIndex = index;
}

std::vector<DocId> IndexSearcher::search(const std::string &query) const
{
    std::vector<DocId> results;
    std::set<Term> terms;

    getQueryTerms(terms, query);

    search(results, terms);

    filter(results, query);

    return results;
}

const InvertedIndex &IndexSearcher::getIndex() const
{
    return mIndex;
}

const DocIdReader *IndexSearcher::getDocIdReader() const
{
    return mDocIdReader;
}

const DocProcessor *IndexSearcher::getDocProcessor() const
{
    return mDocProcessor;
}

const DocProcessor *IndexSearcher::getQueryProcessor() const
{
    return mQueryProcessor;
}

}
