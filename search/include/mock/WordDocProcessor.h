#ifndef WORD_PROCESSOR_H
#define WORD_PROCESSOR_H

#include <set>

#include "SearchDefines.h"
#include "DocProcessor.h"

namespace search
{
class WordDocProcessor: public DocProcessor
{
public:
    virtual ~WordDocProcessor();

    virtual DocProcessor *clone() const;

    virtual bool setDocument(const Document &document);

    virtual void getTerms(std::set<Term> &terms) const;

    virtual const DocDescription *getDocDescription() const;

private:
    void getWords(std::set<Term> &words, const Document &document) const;

    Document mDocument;

    std::set<Term> mTerms;
};

}

#endif//WORD_PROCESSOR_H
