#include "Grammar.h"

#include <set>

#include "BaseExceptions.h"
#include "Logger.h"

namespace search
{
Grammar::Grammar()
{
}

Grammar::Grammar(const Symbols &symbols, const Rules &rules,
        const Symbol &startSymbol)
    :mSymbols(symbols), mRules(rules), mStartSymbol(startSymbol)
{
}

const Rule &Grammar::getRule(size_t ruleIndex) const
{
    if(ruleIndex < mRules.size())
        return mRules[ruleIndex];
    throw base::OutOfBoundError(ruleIndex, mRules.size());
}

size_t Grammar::getRulesCount() const
{
    return mRules.size();
}

const Symbol &Grammar::getStartSymbol() const
{
    return mStartSymbol;
}

const Grammar::Rules &Grammar::getRules() const
{
    return mRules;
}

size_t Grammar::getNonterminalsCount() const
{
    size_t count = 0;
    Symbols::const_iterator iter = mSymbols.begin();
    for(; iter != mSymbols.end(); ++iter)
        if(iter->isNonterminal())
            ++count;
    return count;
}

}
