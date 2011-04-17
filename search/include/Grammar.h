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

    Grammar(const Symbols &symbols, const Rules &rules, const Symbol &startSymbol);

    const Rule &getRule(size_t ruleIndex) const;
    size_t getRulesCount() const;
    const Symbol &getStartSymbol() const;

    const Rules getRules() const;

    size_t getRuleLevel(size_t ruleIndex) const;
    size_t getSymbolLevel(const Symbol &symbol) const;
    size_t getLevelsCount() const;

private:
    void buildRulesLevels();

    Symbols mSymbols;
    Rules mRules;
    Symbol mStartSymbol;

    std::map<size_t, size_t> mRulesLevels;
    std::map<Symbol, size_t> mSymbolsLevels;
    size_t mLevelsCount;
};
}

#endif//GRAMMAR_H
