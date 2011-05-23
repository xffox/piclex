#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include <map>

#include "Symbol.h"
#include "Rule.h"

namespace search
{
class Grammar
{
public:
    typedef std::vector<Symbol> Symbols;
    typedef std::vector<Rule> Rules;

    Grammar();
    Grammar(const Symbols &symbols, const Rules &rules, const Symbol &startSymbol);

    const Rule &getRule(size_t ruleIndex) const;
    size_t getRulesCount() const;
    const Symbol &getStartSymbol() const;

    const Rules &getRules() const;

    size_t getNonterminalsCount() const;

private:
    //TODO: derive symbols not pass
    Symbols mSymbols;
    Rules mRules;
    Symbol mStartSymbol;
};
}

#endif//GRAMMAR_H
