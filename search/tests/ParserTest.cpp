#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Parser.h"

using namespace search;

class ParserTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ParserTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST_SUITE_END();

public:
    void test1()
    {
        Grammar::Rules rules;
        Grammar::Symbols symbols;

        const SymbolValue LETTER = 0;
        const SymbolValue WORD = 1;
        const SymbolValue SPACES = 3;
        const SymbolValue PHRASE = 4;
        const SymbolValue ORWORD = 5;
        const SymbolValue SELECT = 6;

        Symbol letter(NONTERMINAL, LETTER);
        Symbol word(NONTERMINAL, WORD);
        Symbol spaces(NONTERMINAL, SPACES);
        Symbol phrase(NONTERMINAL, PHRASE);
        Symbol orword(NONTERMINAL, ORWORD);
        Symbol select(NONTERMINAL, SELECT);

        symbols.push_back(letter);
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
        rules.push_back( Rule(word, sentence) );
        sentence.clear();

        sentence.push_back(word);
        sentence.push_back(letter);
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

        Parser parser(Grammar(symbols, rules, phrase));

        CPPUNIT_ASSERT(parser.parse("abbb or bc"));
        CPPUNIT_ASSERT(parser.parse("abbb  or  bc"));
        CPPUNIT_ASSERT(parser.parse("or or cdddddd"));
        CPPUNIT_ASSERT(parser.parse("cdddddd or or"));
        CPPUNIT_ASSERT(!parser.parse("aa or"));
        CPPUNIT_ASSERT(!parser.parse("or aa"));
        CPPUNIT_ASSERT(!parser.parse("abbb or bc or"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);
