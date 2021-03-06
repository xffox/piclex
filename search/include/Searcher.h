#ifndef SEARCHER_H
#define SEARCHER_H

#include "SearchDefines.h"

namespace search
{
class DocProvider;
class DocProcessor;
class DocIdReader;
class IndexMaker;
class IndexSearcher;

//! The main search class
class Searcher
{
public:
    Searcher(DocProvider *docProvider, DocProcessor *docProcessor,
            DocProcessor *queryProcessor);
    ~Searcher();

    bool search(std::vector<std::string> &results, const std::string &query);
    void setPath(const std::string &path);

private:
    void makeDocIds(std::vector<DocId> &docIds,
            const std::vector<std::string> &names);

    void getNames(std::vector<std::string> &names,
            const std::vector<DocId> &docIds);

private:
    DocProvider *mDocProvider;
    DocProcessor *mDocProcessor;
    DocProcessor *mQueryProcessor;

    DocIdReader *mDocIdReader;

    IndexMaker *mIndexMaker;

    IndexSearcher *mIndexSearcher;

    DocIdStorage mDocIdStorage;
};

}

#endif//SEARCHER_H
