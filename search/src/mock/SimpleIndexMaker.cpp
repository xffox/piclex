#include "mock/SimpleIndexMaker.h"

#include <memory>

#include "DocIdReader.h"
#include "DocProcessor.h"
#include "IndexToken.h"

namespace search
{
SimpleIndexMaker::SimpleIndexMaker(const DocIdReader *docIdReader,
        const DocProcessor *docProcessor)
    :IndexMaker(docIdReader, docProcessor)
{
}

SimpleIndexMaker::~SimpleIndexMaker()
{
}

void SimpleIndexMaker::tokenize(std::vector<IndexToken> &tokens,
        const std::vector<DocId> &docIds)
{
    const DocIdReader *docIdReader = getDocIdReader();
    if(!docIdReader)
        throw SimpleIndexMakerInternalError();

    const DocProcessor *originalDocProcessor = getDocProcessor();
    if(!originalDocProcessor)
        throw SimpleIndexMakerInternalError();

    std::auto_ptr<DocProcessor> docProcessor(originalDocProcessor->clone());

    Document document;
    std::set<Term> terms;
    std::vector<DocId>::const_iterator docIdsIter = docIds.begin();
    for(; docIdsIter != docIds.end(); ++docIdsIter)
    {
        docIdReader->read(document, *docIdsIter);

        docProcessor->setDocument(document);
        
        docProcessor->getTerms(terms);

        std::set<Term>::const_iterator termsIter = terms.begin();
        for(; termsIter != terms.end(); ++termsIter)
            tokens.push_back(IndexToken(*docIdsIter, *termsIter));
    }
}

void SimpleIndexMaker::makeIndex(InvertedIndex &index,
        const std::vector<IndexToken> &tokens)
{
    index.clear();

    std::vector<IndexToken>::const_iterator tokensIter = tokens.begin();
    for(; tokensIter != tokens.end(); ++tokensIter)
        index.insert(tokensIter->getTerm(), tokensIter->getDocId());
}

}
