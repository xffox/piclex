#include "mock/WordDocProcessor.h"

namespace search
{
WordDocProcessor::~WordDocProcessor()
{
}

DocProcessor *WordDocProcessor::clone() const
{
    return new WordDocProcessor(*this);
}

bool WordDocProcessor::setDocument(const Document &document)
{
    mDocument = document;

    getWords(mTerms, mDocument);

    return true;
}

void WordDocProcessor::getTerms(std::set<Term> &terms) const
{
    terms = mTerms;
}

const DocDescription *WordDocProcessor::getDocDescription() const
{
    return NULL;
}

void WordDocProcessor::getWords(std::set<Term> &words,
        const Document &document) const
{
    words.clear();

    const size_t invalidPos = document.size();
    size_t wordBeginPos = invalidPos;
    size_t i = 0;
    for(i = 0; i < document.size(); ++i)
    {
        if(!isspace(document[i]))
        {
            if(wordBeginPos == invalidPos)
                wordBeginPos = i;
        }
        else
        {
            if(wordBeginPos != invalidPos)
            {
                words.insert(document.substr(wordBeginPos,
                            i - wordBeginPos));

                wordBeginPos = invalidPos;
            }
        }
    }
    if(wordBeginPos != invalidPos)
        words.insert(document.substr(wordBeginPos,
                    i - wordBeginPos));
}

}
