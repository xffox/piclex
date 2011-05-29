#include "Searcher.h"

#include "Logger.h"

#include "BaseExceptions.h"
#include "DocProvider.h"
#include "DocProcessor.h"
#include "DocIdReader.h"
#include "IndexMaker.h"
#include "IndexSearcher.h"
#include "IndexMakerFactory.h"
#include "IndexSearcherFactory.h"

namespace search
{
Searcher::Searcher(DocProvider *docProvider, DocProcessor *docProcessor,
        DocProcessor *queryProcessor)
    :mDocProvider(docProvider), mDocProcessor(docProcessor)
    ,mQueryProcessor(queryProcessor)
    ,mDocIdReader(NULL)
    ,mIndexMaker(NULL), mIndexSearcher(NULL)
{
    mDocIdReader = new DocIdReader(mDocProvider, &mDocIdStorage);

    mIndexMaker = createIndexMaker(mDocIdReader, mDocProcessor);

    mIndexSearcher = createIndexSearcher(mDocIdReader, mDocProcessor,
            mQueryProcessor);
}

Searcher::~Searcher()
{
    delete mIndexSearcher;
    delete mIndexMaker;

    delete mDocIdReader;

    delete mDocProvider;
    delete mDocProcessor;
    delete mQueryProcessor;
}

bool Searcher::search(std::vector<std::string> &results,
        const std::string &query)
{
    base::Log().debug("Searcher: query '%s'", query.c_str());

    if(query.size() > 0)
    {
        std::vector<DocId> docIds;
        if(!mIndexSearcher->search(docIds, query))
        {
            base::Log().debug("invalid query");
            return false;
        }

        getNames(results, docIds);
    }
    else
    {
        mDocIdStorage.getValues(results);
    }

    return true;
}

void Searcher::setPath(const std::string &path)
{
    base::Log().debug("Searcher: set path '%s'", path.c_str());

    std::vector<std::string> names;

    mDocProvider->listNames(names, path);

    std::vector<DocId> docIds;

    makeDocIds(docIds, names);

    mIndexMaker->index(docIds);

    mIndexSearcher->setIndex(mIndexMaker->getIndex());
}

void Searcher::makeDocIds(std::vector<DocId> &docIds,
            const std::vector<std::string> &names)
{
    docIds.clear();

    mDocIdStorage.clear();

    std::vector<std::string>::const_iterator namesIter = names.begin();
    for(; namesIter != names.end(); ++namesIter)
        docIds.push_back(mDocIdStorage.getId(*namesIter));
}

void Searcher::getNames(std::vector<std::string> &names,
        const std::vector<DocId> &docIds)
{
    names.clear();

    std::vector<DocId>::const_iterator docIdsIter = docIds.begin();
    for(; docIdsIter != docIds.end(); ++docIdsIter)
    {
        try
        {
            names.push_back(mDocIdStorage.getValue(*docIdsIter));
        }
        catch(base::NotFoundError &exc)
        {
            base::Log().warning("Searcher: id for name not found: %lu",
                    *docIdsIter);
        }
    }
}

}
