#ifndef IMAGE_DOC_PROCESSOR_H
#define IMAGE_DOC_PROCESSOR_H

#include "DocProcessor.h"
#include "Grammar.h"
#include "TreeBuilderParser.h"

namespace search
{
class ImageDocProcessor: public DocProcessor
{
public:
    ImageDocProcessor();

    virtual ~ImageDocProcessor();

    virtual DocProcessor *clone() const;

    virtual void setDocument(const Document &document);

    virtual void getTerms(std::set<Term> &terms) const;

private:
    void initGrammar();

private:
    void getWords(std::set<Term> &words, const Document &document) const;

    Document mDocument;

    std::set<Term> mTerms;

    Grammar mGrammar;

    TreeBuilderParser mParser;

    SymbolValue mValueLetter;
    SymbolValue mValueLetters;
    SymbolValue mValueWord;
    SymbolValue mValueSpaces;
    SymbolValue mValueObject;
    SymbolValue mValueRelation;
    SymbolValue mValueObjectsRelation;
    SymbolValue mValueObjectsRelations;
    SymbolValue mValueTarget;

    Symbol mSymbolLetter;
    Symbol mSymbolLetters;
    Symbol mSymbolWord;
    Symbol mSymbolSpaces;
    Symbol mSymbolObject;
    Symbol mSymbolRelation;
    Symbol mSymbolObjectsRelation;
    Symbol mSymbolObjectsRelations;
    Symbol mSymbolTarget;
};

}

#endif//IMAGE_PROCESSOR_H
