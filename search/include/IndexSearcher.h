#ifndef INDEX_SEARCHER_H
#define INDEX_SEARCHER_H

#include <vector>
#include <set>

#include "InvertedIndex.h"

namespace search
{
class DocIdReader;
class DocProcessor;

class IndexSearcher
{
public:
    IndexSearcher(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor,
            const DocProcessor *queryProcessor);
    virtual ~IndexSearcher();

    void setIndex(const InvertedIndex &index);

    bool search(std::vector<DocId> &results, const std::string &query) const;

protected:
    const InvertedIndex &getIndex() const;

    const DocIdReader *getDocIdReader() const;
    const DocProcessor *getDocProcessor() const;
    const DocProcessor *getQueryProcessor() const;

private:
    virtual void getQueryTerms(std::set<Term> &terms,
            const DocProcessor *queryProcessor) const = 0;

    virtual void search(std::vector<DocId> &docIds,
            const std::set<Term> &terms) const = 0;

    virtual void filter(std::vector<DocId> &docIds,
            const DocProcessor *queryProcessor) const = 0;

private:
    InvertedIndex mIndex;

    const DocIdReader *mDocIdReader;
    const DocProcessor *mDocProcessor;
    const DocProcessor *mQueryProcessor;
};
}

#endif//INDEX_SEARCHER_H
