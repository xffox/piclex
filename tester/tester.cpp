#include <iostream>

#include "Image.h"
#include "Logger.h"
#include "Parser.h"

using namespace graphics;
using namespace base;
using namespace search;

namespace
{
void printPixel(Pixel pl)
{
    std::cout<<"("<<static_cast<unsigned int>(red(pl))
        <<", "<<static_cast<unsigned int>(green(pl))
        <<", "<<static_cast<unsigned int>(blue(pl))<<")";
}

void printValidation(const Parser &parser, const std::string &str)
{
    std::cout<<"str: '"<<str<<"' is "
        <<(parser.parse(str)?"valid":"invalid")<<std::endl;
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

    printValidation(parser, "abbb or bc");
    printValidation(parser, "abbb  or  bc");
    printValidation(parser, "aa or");
    printValidation(parser, "or or cdddddd");
    printValidation(parser, "cdddddd or or");
    printValidation(parser, "or aa");
    printValidation(parser, "abbb or bc or");
}
}

int main()
{
    Log().setLogWriter( new TimestampedLogWriter(new FileLogWriter(
                    "tester.log")) );

#if 0
    Image a(100, 200);
    Image b(a);
    Image c;
    c = a;

    Log().setSeverity(Logger::DEBUG);
    Log().debug("test %d", 1);
    Log().warning("test %d", 2);
    Log().error("test %s", "3");

    std::cout<<"("<<c.getWidth()<<","<<c.getHeight()<<")"<<std::endl;

    c.set(99, 199, pixel(42, 43, 44));

    Pixel p = c.get(99, 199);

    b = c;

    printPixel(b.get(98, 198));
    std::cout<<std::endl;
    printPixel(b.get(98, 199));
    std::cout<<std::endl;
    printPixel(b.get(99, 198));
    std::cout<<std::endl;
    printPixel(b.get(99, 199));
    std::cout<<std::endl;
#endif

    testParser();

    return 0;
}
