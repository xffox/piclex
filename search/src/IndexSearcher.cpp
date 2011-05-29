#include "IndexSearcher.h"

#include <memory>

#include "Logger.h"
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

bool IndexSearcher::search(std::vector<DocId> &results,
        const std::string &query) const
{
    if(!mQueryProcessor)
        throw base::InternalError();

    std::auto_ptr<DocProcessor> queryProcessor(mQueryProcessor->clone());

    if(!queryProcessor->setDocument(query))
        return false;

    std::set<Term> terms;

    getQueryTerms(terms, queryProcessor.get());

    search(results, terms);

    base::Log().debug("search find %zu docs in index",
            results.size());

    filter(results, queryProcessor.get());

    base::Log().debug("search find %zu docs after filter",
            results.size());

    return true;
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
