#include "Grammar.h"

#include <set>

#include "BaseExceptions.h"
#include "Logger.h"

namespace search
{
Grammar::Grammar(const Symbols &symbols, const Rules &rules,
        const Symbol &startSymbol)
    :mSymbols(symbols), mRules(rules), mStartSymbol(startSymbol)
    ,mLevelsCount(0)
{
    buildRulesLevels();
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

const Grammar::Rules Grammar::getRules() const
{
    return mRules;
}

size_t Grammar::getRuleLevel(size_t ruleIndex) const
{
    if(ruleIndex < mRules.size())
        return (*mRulesLevels.find(ruleIndex)).second;
    throw base::OutOfBoundError(ruleIndex, mRules.size());
}

size_t Grammar::getSymbolLevel(const Symbol &symbol) const
{
    std::map<Symbol, size_t>::const_iterator iter = mSymbolsLevels.find(symbol);
    if(iter != mSymbolsLevels.end())
        return (*iter).second;
    throw base::NotFoundError();
}

void Grammar::buildRulesLevels()
{
    mRulesLevels.clear();

    std::set<Symbol> prevLevelSymbols;
    std::set<Symbol> curLevelSymbols;
    std::set<Symbol>::const_iterator symbolsIter;
    Rules::const_iterator rulesIter;
    prevLevelSymbols.insert(mStartSymbol);
    size_t level = 0;
    while(1)
    {
        symbolsIter = prevLevelSymbols.begin();
        for(; symbolsIter != prevLevelSymbols.end(); ++symbolsIter)
        {
            rulesIter = mRules.begin();
            for(; rulesIter != mRules.end(); ++rulesIter)
                if(rulesIter->getHead() == *symbolsIter)
                {
                    if(mRulesLevels.find(rulesIter-mRules.begin()) ==
                            mRulesLevels.end())
                    {
                        curLevelSymbols.insert(rulesIter->getRuleBody().begin(),
                                rulesIter->getRuleBody().end());

                        mRulesLevels[rulesIter-mRules.begin()] = level;
                    }
                }

            if(mSymbolsLevels.find(*symbolsIter) == mSymbolsLevels.end())
                mSymbolsLevels[*symbolsIter] = level;
        }

        prevLevelSymbols = curLevelSymbols;
        curLevelSymbols.clear();

        if(prevLevelSymbols.size() == 0)
            break;

        ++level;
    }

    mLevelsCount = level + 1;

    base::Log().debug("rules, levels count= %lu", mLevelsCount);
    std::map<size_t, size_t>::const_iterator iter = mRulesLevels.begin();
    for(; iter != mRulesLevels.end(); ++iter)
        base::Log().debug("%s -> %s, level: %lu",
                makeString(mRules[(*iter).first].getHead()).c_str(),
                makeString(mRules[(*iter).first].getRuleBody()).c_str(),
                (*iter).second);

    {
        base::Log().debug("symbols, levels count= %lu", mLevelsCount);
        std::map<Symbol, size_t>::const_iterator symbolsIter =
            mSymbolsLevels.begin();
        for(; symbolsIter != mSymbolsLevels.end(); ++symbolsIter)
            base::Log().debug("%s, level: %lu",
                    makeString((*symbolsIter).first).c_str(),
                    (*symbolsIter).second);
    }
}

size_t Grammar::getLevelsCount() const
{
    return mLevelsCount;
}
}
