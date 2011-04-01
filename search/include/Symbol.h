#ifndef SYMBOL_H
#define SYMBOL_H

namespace search
{
enum SymbolType {TERMINAL, NONTERMINAL};
typedef unsigned int SymbolValue;

class Symbol
{
public:
    Symbol(SymbolType type, SymbolValue value);
    Symbol(char c);

    bool operator==(const Symbol &that);

    SymbolType getType() const;
    SymbolValue getValue() const;

    void setValue(SymbolValue value);

private:
    SymbolType mType;
    SymbolValue mValue;
};
}

#endif//SYMBOL_H
