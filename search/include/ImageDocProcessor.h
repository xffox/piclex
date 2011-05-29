#ifndef IMAGE_DOC_PROCESSOR_H
#define IMAGE_DOC_PROCESSOR_H

#include "DocProcessor.h"
#include "Grammar.h"
#include "TreeBuilderParser.h"
#include "ImageDocDescription.h"

namespace search
{
class ImageDocProcessor: public DocProcessor
{
public:
    ImageDocProcessor();

    virtual ~ImageDocProcessor();

    virtual DocProcessor *clone() const;

    virtual bool setDocument(const Document &document);

    virtual void getTerms(std::set<Term> &terms) const;

    virtual const DocDescription *getDocDescription() const;

private:
    void initGrammar();

private:
    void getWords(std::set<Term> &words, const Document &document) const;

    Document mDocument;

    std::set<Term> mTerms;

    ImageDocDescription mDocDescription;

    Grammar mGrammar;

    TreeBuilderParser mParser;

    SymbolValue mValueLetter;
    SymbolValue mValueLetters;
    SymbolValue mValueWord;
    SymbolValue mValueSpaces;
    SymbolValue mValueObject;
    SymbolValue mValueRelation;
    SymbolValue mValueObjectsRelation;
    SymbolValue mValueDescription;
    SymbolValue mValueDescriptions;
    SymbolValue mValuePhrase;
    SymbolValue mValuePhrases;
    SymbolValue mValueTarget;

    Symbol mSymbolLetter;
    Symbol mSymbolLetters;
    Symbol mSymbolWord;
    Symbol mSymbolSpaces;
    Symbol mSymbolObject;
    Symbol mSymbolRelation;
    Symbol mSymbolObjectsRelation;
    Symbol mSymbolDescription;
    Symbol mSymbolPhrase;
    Symbol mSymbolPhrases;
    Symbol mSymbolTarget;
};

}

#endif//IMAGE_PROCESSOR_H
