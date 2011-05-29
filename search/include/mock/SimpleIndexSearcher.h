#ifndef SIMPLE_INDEX_SEARCHER_H
#define SIMPLE_INDEX_SEARCHER_H

#include "BaseExceptions.h"
#include "IndexSearcher.h"

namespace search
{
class SimpleIndexSearcherInternalError: public base::BaseException
{
};

class SimpleIndexSearcher: public IndexSearcher
{
public:
    SimpleIndexSearcher(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor,
            const DocProcessor *queryProcessor);
    virtual ~SimpleIndexSearcher();

    virtual void getQueryTerms(std::set<Term> &terms,
            const DocProcessor *queryProcessor) const;

    virtual void search(std::vector<DocId> &docIds,
            const std::set<Term> &terms) const;

    virtual void filter(std::vector<DocId> &docIds,
            const DocProcessor *queryProcessor) const;
};

}

#endif//SIMPLE_INDEX_SEARCHER_H
