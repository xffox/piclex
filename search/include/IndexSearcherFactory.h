#ifndef INDEX_SEARCHER_FACTORY_H
#define INDEX_SEARCHER_FACTORY_H

namespace search
{
class IndexSearcher;
class DocIdReader;
class DocProcessor;

IndexSearcher *createIndexSearcher(const DocIdReader *docIdReader,
        const DocProcessor *docProcessor,
        const DocProcessor *queryProcessor);
}

#endif//INDEX_SEARCHER_FACTORY_H
