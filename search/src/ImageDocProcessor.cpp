#include "ImageDocProcessor.h"

#include "Logger.h"
#include "BaseUtil.h"
#include "SubsentenceGatherer.h"
#include "DocDescriptionGatherer.h"

namespace search
{
ImageDocProcessor::ImageDocProcessor()
{
    initGrammar();

    mParser.setGrammar(mGrammar);
}

ImageDocProcessor::~ImageDocProcessor()
{
}

DocProcessor *ImageDocProcessor::clone() const
{
    return new ImageDocProcessor(*this);
}

bool ImageDocProcessor::setDocument(const Document &document)
{
    if(mParser.parse(document))
    {
        mDocument = document;

        mTerms.clear();
        mDocDescription.clear();

        SubsentenceGatherer gatherer(mDocument, mSymbolObject);

        mParser.getParseTree().root().accept(&gatherer);

        base::vectorToSet(mTerms, gatherer.getSubsentences());

        DocDescriptionGatherer docDescriptionGatherer(&mDocDescription,
                mDocument, mSymbolObject, mSymbolRelation,
                mSymbolDescription);

        mParser.getParseTree().root().accept(&docDescriptionGatherer);

        return true;
    }
    base::Log().warning("invalid image description [%s]",
            document.c_str());
    return false;
}

void ImageDocProcessor::getTerms(std::set<Term> &terms) const
{
    terms = mTerms;
}

const DocDescription *ImageDocProcessor::getDocDescription() const
{
    return &mDocDescription;
}

void ImageDocProcessor::initGrammar()
{
    Grammar::Rules rules;
    Grammar::Symbols symbols;

    mValueLetter = 0;
    mValueLetters = 1;
    mValueWord = 2;
    mValueSpaces = 3;
    mValueObject = 4;
    mValueRelation = 5;
    mValueObjectsRelation = 6;
    mValueDescription = 7;
    mValuePhrase = 8;
    mValuePhrases = 9;
    mValueTarget = 10;

    mSymbolLetter = Symbol(NONTERMINAL, mValueLetter);
    mSymbolLetters = Symbol(NONTERMINAL, mValueLetters);
    mSymbolWord = Symbol(NONTERMINAL, mValueWord);
    mSymbolSpaces = Symbol(NONTERMINAL, mValueSpaces);
    mSymbolObject = Symbol(NONTERMINAL, mValueObject);
    mSymbolRelation = Symbol(NONTERMINAL, mValueRelation);
    mSymbolObjectsRelation = Symbol(NONTERMINAL, mValueObjectsRelation);
    mSymbolDescription = Symbol(NONTERMINAL, mValueDescription);
    mSymbolPhrase = Symbol(NONTERMINAL, mValuePhrase);
    mSymbolPhrases = Symbol(NONTERMINAL, mValuePhrases);
    mSymbolTarget = Symbol(NONTERMINAL, mValueTarget);

    symbols.push_back(mSymbolLetter);
    symbols.push_back(mSymbolLetters);
    symbols.push_back(mSymbolWord);
    symbols.push_back(mSymbolSpaces);
    symbols.push_back(mSymbolObject);
    symbols.push_back(mSymbolRelation);
    symbols.push_back(mSymbolObjectsRelation);
    symbols.push_back(mSymbolDescription);
    symbols.push_back(mSymbolPhrase);
    symbols.push_back(mSymbolPhrases);
    symbols.push_back(mSymbolTarget);
    symbols.push_back(Symbol('a'));
    symbols.push_back(Symbol('b'));
    symbols.push_back(Symbol('c'));
    symbols.push_back(Symbol('d'));
    symbols.push_back(Symbol('e'));
    symbols.push_back(Symbol('f'));
    symbols.push_back(Symbol('g'));
    symbols.push_back(Symbol('h'));
    symbols.push_back(Symbol('i'));
    symbols.push_back(Symbol('j'));
    symbols.push_back(Symbol('k'));
    symbols.push_back(Symbol('l'));
    symbols.push_back(Symbol('m'));
    symbols.push_back(Symbol('n'));
    symbols.push_back(Symbol('o'));
    symbols.push_back(Symbol('p'));
    symbols.push_back(Symbol('q'));
    symbols.push_back(Symbol('r'));
    symbols.push_back(Symbol('s'));
    symbols.push_back(Symbol('t'));
    symbols.push_back(Symbol('u'));
    symbols.push_back(Symbol('v'));
    symbols.push_back(Symbol('w'));
    symbols.push_back(Symbol('x'));
    symbols.push_back(Symbol('y'));
    symbols.push_back(Symbol('z'));

    rules.push_back( Rule(mSymbolLetter, sentence("a")) );
    rules.push_back( Rule(mSymbolLetter, sentence("b")) );
    rules.push_back( Rule(mSymbolLetter, sentence("c")) );
    rules.push_back( Rule(mSymbolLetter, sentence("d")) );
    rules.push_back( Rule(mSymbolLetter, sentence("e")) );
    rules.push_back( Rule(mSymbolLetter, sentence("f")) );
    rules.push_back( Rule(mSymbolLetter, sentence("g")) );
    rules.push_back( Rule(mSymbolLetter, sentence("h")) );
    rules.push_back( Rule(mSymbolLetter, sentence("i")) );
    rules.push_back( Rule(mSymbolLetter, sentence("j")) );
    rules.push_back( Rule(mSymbolLetter, sentence("k")) );
    rules.push_back( Rule(mSymbolLetter, sentence("l")) );
    rules.push_back( Rule(mSymbolLetter, sentence("m")) );
    rules.push_back( Rule(mSymbolLetter, sentence("n")) );
    rules.push_back( Rule(mSymbolLetter, sentence("o")) );
    rules.push_back( Rule(mSymbolLetter, sentence("p")) );
    rules.push_back( Rule(mSymbolLetter, sentence("q")) );
    rules.push_back( Rule(mSymbolLetter, sentence("r")) );
    rules.push_back( Rule(mSymbolLetter, sentence("s")) );
    rules.push_back( Rule(mSymbolLetter, sentence("t")) );
    rules.push_back( Rule(mSymbolLetter, sentence("u")) );
    rules.push_back( Rule(mSymbolLetter, sentence("v")) );
    rules.push_back( Rule(mSymbolLetter, sentence("w")) );
    rules.push_back( Rule(mSymbolLetter, sentence("x")) );
    rules.push_back( Rule(mSymbolLetter, sentence("y")) );
    rules.push_back( Rule(mSymbolLetter, sentence("z")) );
    rules.push_back( Rule(mSymbolSpaces, sentence(" ")) );

    Sentence sentence;

    sentence.push_back(mSymbolLetter);
    rules.push_back( Rule(mSymbolLetters, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolLetters);
    sentence.push_back(mSymbolLetter);
    rules.push_back( Rule(mSymbolLetters, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolLetters);
    rules.push_back( Rule(mSymbolWord, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolSpaces);
    sentence.push_back(Symbol(' '));
    rules.push_back( Rule(mSymbolSpaces, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolWord);
    rules.push_back( Rule(mSymbolObject, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolWord);
    rules.push_back( Rule(mSymbolRelation, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolObject);
    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolRelation);
    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolObject);
    rules.push_back( Rule(mSymbolObjectsRelation, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolObjectsRelation);
    rules.push_back( Rule(mSymbolDescription, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolObject);
    rules.push_back( Rule(mSymbolDescription, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolDescription);
    rules.push_back( Rule(mSymbolPhrase, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolDescription);
    rules.push_back( Rule(mSymbolPhrase, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolDescription);
    sentence.push_back(mSymbolSpaces);
    rules.push_back( Rule(mSymbolPhrase, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolDescription);
    sentence.push_back(mSymbolSpaces);
    rules.push_back( Rule(mSymbolPhrase, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolPhrase);
    sentence.push_back(',');
    sentence.push_back(mSymbolPhrase);
    rules.push_back( Rule(mSymbolPhrases, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolPhrases);
    sentence.push_back(',');
    sentence.push_back(mSymbolPhrase);
    rules.push_back( Rule(mSymbolPhrases, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolPhrase);
    rules.push_back( Rule(mSymbolTarget, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolPhrases);
    rules.push_back( Rule(mSymbolTarget, sentence) );
    sentence.clear();

    mGrammar = Grammar(symbols, rules, mSymbolTarget);
}

};
