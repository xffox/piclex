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

class Searcher
{
public:
    Searcher(DocProvider *docProvider, DocProcessor *docProcessor,
            DocProcessor *queryProcessor);
    ~Searcher();

    std::vector<std::string> search(const std::string &query);
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
