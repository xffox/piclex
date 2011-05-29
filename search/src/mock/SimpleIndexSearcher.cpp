#include "mock/SimpleIndexSearcher.h"

#include <memory>

#include "Logger.h"
#include "BaseExceptions.h"
#include "DocProcessor.h"
#include "DocDescription.h"
#include "DocIdReader.h"

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
        const DocProcessor *queryProcessor) const
{
    if(!queryProcessor)
        throw base::InternalError();

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

    base::Log().debug("find %lu documents for %lu terms", docIds.size(),
            terms.size());
}

void SimpleIndexSearcher::filter(std::vector<DocId> &docIds,
        const DocProcessor *queryProcessor) const
{
    if(!queryProcessor)
        throw base::InternalError();

    const DocDescription *queryDocDescription =
        queryProcessor->getDocDescription();
    if(queryDocDescription)
    {
        const DocProcessor *originalDocProcessor = getDocProcessor();
        if(!originalDocProcessor)
            throw SimpleIndexSearcherInternalError();
        std::auto_ptr<DocProcessor> docProcessor(
                originalDocProcessor->clone());

        const DocIdReader *docIdReader = getDocIdReader();
        if(!docIdReader)
            throw SimpleIndexSearcherInternalError();

        std::vector<DocId>::iterator docIdsIter = docIds.begin();
        std::string docData;
        while(docIdsIter != docIds.end())
        {
            docIdReader->read(docData, *docIdsIter);

            docProcessor->setDocument(docData);
            if( docProcessor->getDocDescription() &&
                    queryDocDescription->isSubsetEq(
                        *docProcessor->getDocDescription()) )
            {
                ++docIdsIter;
            }
            else
            {
                docIdsIter = docIds.erase(docIdsIter);
            }
        }
    }
}

}
