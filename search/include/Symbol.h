#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

namespace search
{
enum SymbolType {TERMINAL, NONTERMINAL};
typedef unsigned int SymbolValue;

class Symbol
{
public:
    Symbol(SymbolType type, SymbolValue value);
    Symbol(char c);

    bool operator==(const Symbol &that) const;
    bool operator!=(const Symbol &that) const;

    bool operator<(const Symbol &that) const;

    SymbolType getType() const;
    SymbolValue getValue() const;

    bool isTerminal() const;
    bool isNonterminal() const;

    void setValue(SymbolValue value);

private:
    SymbolType mType;
    SymbolValue mValue;
};

const std::string makeString(const Symbol &symbol);
}

#endif//SYMBOL_H
