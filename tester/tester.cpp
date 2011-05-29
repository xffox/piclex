#include <iostream>

#include <list>
#include <set>

#include "Logger.h"
#include "Parser.h"
#include "TreeBuilderParser.h"
#include "Matrix3d.h"

#include "Tree.h"
#include "TreeVisitor.h"
#include "FsUtil.h"
#include "FsDocProvider.h"

#include "mock/WordDocProcessor.h"

using namespace base;
using namespace search;

namespace
{
class PrintTreeVisitor: public TreeVisitor<ParseNode>
{
public:
    PrintTreeVisitor(const Sentence &str)
        :mStr(str)
    {
    }

    virtual ~PrintTreeVisitor(){}

    virtual void visit(const TreeIterator<ParseNode> &iterator)
    {
        if(!iterator.isEnd())
            std::cout<<makeString((*iterator).getSymbol())
                <<" - "<<makeString(mStr, (*iterator).getBeginPosition(),
                        (*iterator).getSize())<<'\n';
    }

private:
    Sentence mStr;
};

void printTree(const TreeBuilderParser &parser,
        TreeIterator<ParseNode> &iter)
{
    if(iter.isEnd())
        return;

    std::cout<<makeString((*iter).getSymbol())
        <<" - "<<makeString(parser.getStr(), (*iter).getBeginPosition(),
                (*iter).getSize())<<'\n';

    Tree<ParseNode>::Iterator downIter = iter;
    for(size_t i = 0; i < downIter.getChildsCount(); ++i)
    {
        downIter.down(i);
        printTree(parser, downIter);
        downIter.up();
    }
}

void printValidation(Parser &parser, const std::string &str)
{
    std::cout<<"str: '"<<str<<"' is "
        <<(parser.parse(str)?"valid":"invalid")<<std::endl;
}

void printParseTree(TreeBuilderParser &parser, const std::string &str)
{
    parser.parse(str);

    std::cout<<"str: '"<<str<<"' is "
        <<(parser.isValid()?"valid":"invalid")<<std::endl;

    TreeIterator<ParseNode> iter = parser.getParseTree().root();
    PrintTreeVisitor visitor(parser.getStr());
    iter.accept(&visitor);
//    printTree(parser, iter);
}

void testParser()
{
    Grammar::Rules rules;
    Grammar::Symbols symbols;

    const SymbolValue mValueLetter = 0;
    const SymbolValue mValueLetters = 1;
    const SymbolValue mValueWord = 2;
    const SymbolValue mValueSpaces = 3;
    const SymbolValue mValueObject = 4;
    const SymbolValue mValueRelation = 5;
    const SymbolValue mValueObjectsRelation = 6;
    const SymbolValue mValueDescription = 7;
    const SymbolValue mValueDescriptions = 8;
    const SymbolValue mValueTarget = 9;

    Symbol mSymbolLetter = Symbol(NONTERMINAL, mValueLetter);
    Symbol mSymbolLetters = Symbol(NONTERMINAL, mValueLetters);
    Symbol mSymbolWord = Symbol(NONTERMINAL, mValueWord);
    Symbol mSymbolSpaces = Symbol(NONTERMINAL, mValueSpaces);
    Symbol mSymbolObject = Symbol(NONTERMINAL, mValueObject);
    Symbol mSymbolRelation = Symbol(NONTERMINAL, mValueRelation);
    Symbol mSymbolObjectsRelation = Symbol(NONTERMINAL, mValueObjectsRelation);
    Symbol mSymbolDescription = Symbol(NONTERMINAL, mValueDescription);
    Symbol mSymbolDescriptions = Symbol(NONTERMINAL, mValueDescriptions);
    Symbol mSymbolTarget = Symbol(NONTERMINAL, mValueTarget);

    symbols.push_back(mSymbolLetter);
    symbols.push_back(mSymbolLetters);
    symbols.push_back(mSymbolWord);
    symbols.push_back(mSymbolSpaces);
    symbols.push_back(mSymbolObject);
    symbols.push_back(mSymbolRelation);
    symbols.push_back(mSymbolObjectsRelation);
    symbols.push_back(mSymbolDescription);
    symbols.push_back(mSymbolDescriptions);
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
    rules.push_back( Rule(mSymbolDescriptions, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolDescription);
    rules.push_back( Rule(mSymbolDescriptions, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolDescription);
    sentence.push_back(mSymbolSpaces);
    rules.push_back( Rule(mSymbolDescriptions, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolSpaces);
    sentence.push_back(mSymbolDescription);
    sentence.push_back(mSymbolSpaces);
    rules.push_back( Rule(mSymbolDescriptions, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolDescriptions);
    sentence.push_back(',');
    sentence.push_back(mSymbolDescriptions);
    rules.push_back( Rule(mSymbolDescriptions, sentence) );
    sentence.clear();

    sentence.push_back(mSymbolDescriptions);
    rules.push_back( Rule(mSymbolTarget, sentence) );
    sentence.clear();

    Parser parser(Grammar(symbols, rules, mSymbolTarget));

    printValidation(parser, "abbb or bc");
    printValidation(parser, "abbb  or  bc");
    printValidation(parser, "aa or");
    printValidation(parser, "or or cdddddd");
    printValidation(parser, "cdddddd or or");
    printValidation(parser, "or aa");
    printValidation(parser, "abbb or bc or");
    printValidation(parser, "abbb or bc, cd or ls");
}

void testTree()
{
    Tree<int> tree;

    Tree<int>::Iterator iter = tree.root();
    tree.insert(iter, 42);
    tree.insert(iter, 43);
    iter.up();
    iter.up();
    tree.insert(iter, 44);
    iter.up();
    tree.insertChild(iter, 45, 1);
    tree.appendChild(iter, 46);
    iter.down(2);
    tree.appendChild(iter, 47);

#if 0
    iter = tree.root();
    while(!iter.isEnd())
    {
        std::cout<<*iter<<'\n';
        iter.down(0);
    }
#endif
}

void testTreeBuilderParserInstance()
{
    Grammar::Rules rules;
    Grammar::Symbols symbols;

    const SymbolValue mValueLetter = 0;
    const SymbolValue mValueLetters = 1;
    const SymbolValue mValueWord = 2;
    const SymbolValue mValueSpaces = 3;
    const SymbolValue mValueObject = 4;
    const SymbolValue mValueRelation = 5;
    const SymbolValue mValueObjectsRelation = 6;
    const SymbolValue mValueDescription = 7;
    const SymbolValue mValuePhrase = 8;
    const SymbolValue mValuePhrases = 9;
    const SymbolValue mValueTarget = 10;

    Symbol mSymbolLetter = Symbol(NONTERMINAL, mValueLetter);
    Symbol mSymbolLetters = Symbol(NONTERMINAL, mValueLetters);
    Symbol mSymbolWord = Symbol(NONTERMINAL, mValueWord);
    Symbol mSymbolSpaces = Symbol(NONTERMINAL, mValueSpaces);
    Symbol mSymbolObject = Symbol(NONTERMINAL, mValueObject);
    Symbol mSymbolRelation = Symbol(NONTERMINAL, mValueRelation);
    Symbol mSymbolObjectsRelation = Symbol(NONTERMINAL, mValueObjectsRelation);
    Symbol mSymbolDescription = Symbol(NONTERMINAL, mValueDescription);
    Symbol mSymbolPhrase = Symbol(NONTERMINAL, mValuePhrase);
    Symbol mSymbolPhrases = Symbol(NONTERMINAL, mValuePhrases);
    Symbol mSymbolTarget = Symbol(NONTERMINAL, mValueTarget);

    symbols.push_back(mSymbolLetter);
    symbols.push_back(mSymbolLetters);
    symbols.push_back(mSymbolWord);
    symbols.push_back(mSymbolSpaces);
    symbols.push_back(mSymbolObject);
    symbols.push_back(mSymbolRelation);
    symbols.push_back(mSymbolObjectsRelation);
    symbols.push_back(mSymbolDescription);
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

    TreeBuilderParser parser(Grammar(symbols, rules, mSymbolTarget));

    printParseTree(parser, "abbb or bc");
    printParseTree(parser, "abbb  or  bc");
    printParseTree(parser, "aa or");
    printParseTree(parser, "or or cdddddd");
    printParseTree(parser, "cdddddd or or");
    printParseTree(parser, "or aa");
    printParseTree(parser, "abbb or bc or");
    printParseTree(parser, "ab  or   bc");
    printParseTree(parser, "aorb or bc");
    printParseTree(parser, "liberty or death");
    printParseTree(parser, "  liberty or death");
    printParseTree(parser, " liberty or death  ");
    printParseTree(parser, "circle left square, square left circle");
    printParseTree(parser, "circle left square, square left circle,"
            "triangle on circle");
    printParseTree(parser, "circle and circle");
    printParseTree(parser, "circle left circle, square down circle, "
            "circle in square, square in square");
}
}

class ExtensionFilter: public FsFilter
{
public:
    ExtensionFilter(const std::string &extension)
        :mDotExtension(extension)
    {
        if(extension.length() == 0)
            throw InvalidArgument();

        mDotExtension.insert(0, ".");
    }

    bool isValid(const std::string &str)
    {
        // dot at the beginning of the word is not the extension delimeter dot
        if(str.length() <= mDotExtension.length())
            return false;

        return !str.compare(str.length() - mDotExtension.length(),
                mDotExtension.length(), mDotExtension);
    }

private:
    std::string mDotExtension;
};

int main()
{
    Log().setLogWriter( new TimestampedLogWriter(new FileLogWriter(
                    "tester.log")) );

#if 0
    testParser();

    testTree();
#endif

    testTreeBuilderParserInstance();

#if 0
    ExtensionFilter filter("txt");

    std::vector<std::string> files;
    FsUtil::listFiles(files, "/home/fox");

    FsDocProvider docProvider;

    std::vector<std::string>::const_iterator iter;
    for(iter = files.begin(); iter != files.end(); ++iter)
        std::cout<<*iter<<'\n';
#endif

#if 0
    if(files.size() > 0)
    {
#if 0
        std::string data;
        docProvider.read(data, files[0]);
        std::cout<<"data [\n";
        std::cout<<data;
        std::cout<<"]\n";
        
        WordDocProcessor processor;
        processor.setDocument(data);

        std::set<Term> terms;
        processor.getTerms(terms);
#endif

#if 0
        std::cout<<"Words:\n";
        std::set<Term>::const_iterator termsIter = terms.begin();
        for(; termsIter != terms.end(); ++termsIter)
            std::cout<<*termsIter<<'\n';
#endif
    }
#endif

#if 0
    const size_t pages = 5;
    const size_t rows = 6;
    const size_t columns = 7;
    Matrix3d<unsigned int> m(pages, rows, columns);

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    for(i = 0; i < m.getPages(); ++i)
        for(j = 0; j < m.getRows(); ++j)
            for(k = 0; k < m.getColumns(); ++k)
                m.set(i, j, k, rows*columns * i + columns * j + k);

    const size_t newPages = pages * 2;
    const size_t newRows = rows * 2;
    const size_t newColumns = columns * 2;
    const unsigned int val = 1000;
    m.resize(newPages, newRows, newColumns, val);

    for(i = 0; i < m.getPages(); ++i)
        for(j = 0; j < m.getRows(); ++j)
            for(k = 0; k < m.getColumns(); ++k)
                std::cout<<m.get(i, j, k)<<' '
                    <<((i < pages && j < rows && k < columns)?
                            rows*columns * i + columns * j + k:val)<<'\n';
#endif

    return 0;
}
