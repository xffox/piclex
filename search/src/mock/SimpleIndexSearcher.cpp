#include "mock/SimpleIndexSearcher.h"

#include <memory>

#include "DocProcessor.h"

namespace search
{
SimpleIndexSearcher::SimpleIndexSearcher(const DocIdReader *docIdReader,
        const DocProcessor *docProcessor,
        const DocProcessor *queryProcessor)
    :IndexSearcher(docIdReader, docProcessor, queryProcessor)
{
}

SimpleIndexSearcher::~SimpleIndexSearcher()
{
}

void SimpleIndexSearcher::getQueryTerms(std::set<Term> &terms,
        const std::string &query) const
{
    const DocProcessor *originalQueryProcessor = getQueryProcessor();
    if(!originalQueryProcessor)
        throw SimpleIndexSearcherInternalError();

    std::auto_ptr<DocProcessor> queryProcessor(originalQueryProcessor->clone());

    queryProcessor->setDocument(query);

    queryProcessor->getTerms(terms);
}

void SimpleIndexSearcher::search(std::vector<DocId> &docIds,
        const std::set<Term> &terms) const
{
    std::set<Term>::const_iterator termsIter = terms.begin();
    if(termsIter == terms.end())
        return;

    //TODO: optimize it
    docIds = getIndex().getPostings(*termsIter);
    ++termsIter;

    for(; termsIter != terms.end(); ++termsIter)
        docIds = docIds & getIndex().getPostings(*termsIter);
}

void SimpleIndexSearcher::filter(std::vector<DocId> &docIds,
        const std::string &query) const
{
}

}
