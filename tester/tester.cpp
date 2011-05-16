#include <iostream>

#include <list>
#include <set>

#include "Logger.h"
#include "Parser.h"
#include "TreeBuilderParserInstance.h"

#include "Tree.h"
#include "FsUtil.h"
#include "FsDocProvider.h"

#include "mock/WordDocProcessor.h"

using namespace base;
using namespace search;

namespace
{
void printTree(const TreeBuilderParserInstance &parser,
        TreeIterator<ParseNode> &iter)
{
    if(iter.isEnd())
        return;

    std::cout<<makeString((*iter).getSymbol())
        <<" - "<<makeString(parser.getStr(), (*iter).getBeginPosition(),
                (*iter).getEndPosition())<<'\n';

    Tree<ParseNode>::Iterator downIter = iter;
    for(size_t i = 0; i < downIter.getChildsCount(); ++i)
    {
        downIter.down(i);
        printTree(parser, downIter);
        downIter.up();
    }
}

void printValidation(const Parser &parser, const std::string &str)
{
    std::cout<<"str: '"<<str<<"' is "
        <<(parser.parse(str)?"valid":"invalid")<<std::endl;
}

void printParseTree(const Grammar &grammar, const std::string &str)
{
    TreeBuilderParserInstance parser(grammar, str);
    parser.parse();

    std::cout<<"str: '"<<str<<"' is "
        <<(parser.isValid()?"valid":"invalid")<<std::endl;

    TreeIterator<ParseNode> iter = parser.getParseTree().root();
    printTree(parser, iter);
}

void testParser()
{
    Grammar::Rules rules;
    Grammar::Symbols symbols;

    const SymbolValue LETTER = 0;
    const SymbolValue WORD = 1;
    const SymbolValue SPACES = 3;
    const SymbolValue PHRASE = 4;
    const SymbolValue ORWORD = 5;
    const SymbolValue SELECT = 6;
    const SymbolValue LETTERS = 7;

    Symbol letter(NONTERMINAL, LETTER);
    Symbol word(NONTERMINAL, WORD);
    Symbol spaces(NONTERMINAL, SPACES);
    Symbol phrase(NONTERMINAL, PHRASE);
    Symbol orword(NONTERMINAL, ORWORD);
    Symbol select(NONTERMINAL, SELECT);
    Symbol letters(NONTERMINAL, LETTERS);

    symbols.push_back(letter);
    symbols.push_back(letters);
    symbols.push_back(word);
    symbols.push_back(spaces);
    symbols.push_back(Symbol('a'));
    symbols.push_back(Symbol('b'));
    symbols.push_back(Symbol('c'));
    symbols.push_back(Symbol('d'));

    rules.push_back( Rule(letter, sentence("a")) );
    rules.push_back( Rule(letter, sentence("b")) );
    rules.push_back( Rule(letter, sentence("c")) );
    rules.push_back( Rule(letter, sentence("d")) );
    rules.push_back( Rule(letter, sentence("r")) );
    rules.push_back( Rule(letter, sentence("o")) );
    rules.push_back( Rule(spaces, sentence(" ")) );

    Sentence sentence;
    sentence.push_back(spaces);
    sentence.push_back(Symbol(' '));
    rules.push_back( Rule(spaces, sentence) );
    sentence.clear();

    sentence.push_back(letter);
    rules.push_back( Rule(letters, sentence) );
    sentence.clear();

    sentence.push_back(letters);
    sentence.push_back(letter);
    rules.push_back( Rule(letters, sentence) );
    sentence.clear();

    sentence.push_back(letters);
    rules.push_back( Rule(word, sentence) );
    sentence.clear();

    sentence.push_back(spaces);
    sentence.push_back(Symbol('o'));
    sentence.push_back(Symbol('r'));
    sentence.push_back(spaces);
    rules.push_back( Rule(orword, sentence) );
    sentence.clear();

    sentence.push_back(letters);
    sentence.push_back(orword);
    sentence.push_back(letters);
    rules.push_back( Rule(select, sentence) );
    sentence.clear();

    sentence.push_back(select);
    rules.push_back( Rule(phrase, sentence) );
    sentence.clear();

    Parser parser(Grammar(symbols, rules, phrase));

    printValidation(parser, "abbb or bc");
    printValidation(parser, "abbb  or  bc");
    printValidation(parser, "aa or");
    printValidation(parser, "or or cdddddd");
    printValidation(parser, "cdddddd or or");
    printValidation(parser, "or aa");
    printValidation(parser, "abbb or bc or");
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

    const SymbolValue LETTER = 0;
    const SymbolValue WORD = 1;
    const SymbolValue SPACES = 3;
    const SymbolValue PHRASE = 4;
    const SymbolValue ORWORD = 5;
    const SymbolValue SELECT = 6;
    const SymbolValue LETTERS = 7;

    Symbol letter(NONTERMINAL, LETTER);
    Symbol word(NONTERMINAL, WORD);
    Symbol spaces(NONTERMINAL, SPACES);
    Symbol phrase(NONTERMINAL, PHRASE);
    Symbol orword(NONTERMINAL, ORWORD);
    Symbol select(NONTERMINAL, SELECT);
    Symbol letters(NONTERMINAL, LETTERS);

    symbols.push_back(letter);
    symbols.push_back(letters);
    symbols.push_back(word);
    symbols.push_back(spaces);
    symbols.push_back(Symbol('a'));
    symbols.push_back(Symbol('b'));
    symbols.push_back(Symbol('c'));
    symbols.push_back(Symbol('d'));

    rules.push_back( Rule(letter, sentence("a")) );
    rules.push_back( Rule(letter, sentence("b")) );
    rules.push_back( Rule(letter, sentence("c")) );
    rules.push_back( Rule(letter, sentence("d")) );
    rules.push_back( Rule(letter, sentence("r")) );
    rules.push_back( Rule(letter, sentence("o")) );
    rules.push_back( Rule(letter, sentence("l")) );
    rules.push_back( Rule(letter, sentence("i")) );
    rules.push_back( Rule(letter, sentence("e")) );
    rules.push_back( Rule(letter, sentence("t")) );
    rules.push_back( Rule(letter, sentence("y")) );
    rules.push_back( Rule(letter, sentence("h")) );
    rules.push_back( Rule(spaces, sentence(" ")) );

    Sentence sentence;
    sentence.push_back(spaces);
    sentence.push_back(Symbol(' '));
    rules.push_back( Rule(spaces, sentence) );
    sentence.clear();

    sentence.push_back(letter);
    rules.push_back( Rule(letters, sentence) );
    sentence.clear();

    sentence.push_back(letters);
    sentence.push_back(letter);
    rules.push_back( Rule(letters, sentence) );
    sentence.clear();

    sentence.push_back(letters);
    rules.push_back( Rule(word, sentence) );
    sentence.clear();

    sentence.push_back(spaces);
    sentence.push_back(Symbol('o'));
    sentence.push_back(Symbol('r'));
    sentence.push_back(spaces);
    rules.push_back( Rule(orword, sentence) );
    sentence.clear();

    sentence.push_back(word);
    sentence.push_back(orword);
    sentence.push_back(word);
    rules.push_back( Rule(select, sentence) );
    sentence.clear();

    sentence.push_back(select);
    rules.push_back( Rule(phrase, sentence) );
    sentence.clear();

    printParseTree(Grammar(symbols, rules, phrase), "abbb or bc");
    printParseTree(Grammar(symbols, rules, phrase), "abbb  or  bc");
    printParseTree(Grammar(symbols, rules, phrase), "aa or");
    printParseTree(Grammar(symbols, rules, phrase), "or or cdddddd");
    printParseTree(Grammar(symbols, rules, phrase), "cdddddd or or");
    printParseTree(Grammar(symbols, rules, phrase), "or aa");
    printParseTree(Grammar(symbols, rules, phrase), "abbb or bc or");
    printParseTree(Grammar(symbols, rules, phrase), "ab  or   bc");
    printParseTree(Grammar(symbols, rules, phrase), "aorb or bc");
    printParseTree(Grammar(symbols, rules, phrase), "liberty or death");
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

#if 0
    testTreeBuilderParserInstance();
#endif

    ExtensionFilter filter("txt");

    std::vector<std::string> files;
    FsUtil::listFiles(files, "/home/fox");

    FsDocProvider docProvider;

    std::vector<std::string>::const_iterator iter;
    for(iter = files.begin(); iter != files.end(); ++iter)
        std::cout<<*iter<<'\n';

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

    return 0;
}
