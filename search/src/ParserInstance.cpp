#include "ParserInstance.h"

#include <cassert>

#include "Logger.h"

using namespace base;

namespace search
{
ParserInstance::ParserInstance(const Grammar &grammar,
        const std::string &str)
    :mGrammar(grammar), mStr(sentence(str))
    ,mValid(false)
{
    mParsedSentence = mStr;
    mValid = parse();
}

ParserInstance::~ParserInstance()
{
}

bool ParserInstance::isValid() const
{
    return mValid;
}

bool ParserInstance::parse()
{
    return process();
}

bool ParserInstance::process()
{
    size_t position = 0;

    size_t ruleIndex = 0;
    const size_t rulesCount = mGrammar.getRulesCount();

    Log().debug("parse begin");
    Log().debug("parse: %s", makeString(mParsedSentence).c_str());

    position = 0;
    while(position < mParsedSentence.size())
    {
        if((ruleIndex = process(position)) < rulesCount)
        {
            position -= mGrammar.getRule(ruleIndex).getBodyLength() - 1;

            Log().debug("parse: %s", makeString(mParsedSentence).c_str());

            position = 0;
        }
        else
        {
            ++position;
        }
    }

    bool valid = mParsedSentence.size() == 1 &&
        mParsedSentence[0] == mGrammar.getStartSymbol();

    Log().debug("sentence %s", valid?"valid":"invalid");
    Log().debug("parse end");

    return valid;
}

size_t ParserInstance::process(size_t position)
{
    size_t ruleIndex = 0;
    if(position < mParsedSentence.size())
    {
        ruleIndex = getRule(position);
        if(ruleIndex < mGrammar.getRulesCount())
        {
            if( getSubsentenceMaxSymbolLevel(position,
                        mGrammar.getRule(ruleIndex).getBodyLength()) >=
                    getSubsentenceMaxSymbolLevel(position +
                        mGrammar.getRule(ruleIndex).getBodyLength()) )
            {
                processRewrite(position, ruleIndex);

                rewriteBodyWithHead(position, ruleIndex);

                return ruleIndex;
            }
        }
    }

    return mGrammar.getRulesCount();
}

size_t ParserInstance::getRule(size_t position) const
{
    if(position >= mParsedSentence.size())
        return mGrammar.getRulesCount();;

    size_t ruleIndex = mGrammar.getRulesCount();

    Rules rules = getRules(mParsedSentence[position]);

    size_t processedSymbols = 0;
    Rules::iterator rulesIter;
    while(rules.size() > 0)
    {
        rulesIter = rules.begin();
        while(rulesIter != rules.end())
        {
            if(processedSymbols < rulesIter->getBodyLength())
            {
                if(position + processedSymbols >= mParsedSentence.size() ||
                        mParsedSentence[position + processedSymbols] !=
                        rulesIter->getBody(processedSymbols))
                    rulesIter = rules.erase(rulesIter);
                else
                    ++rulesIter;
            }
            else
            {
                ruleIndex = getRuleIndex(*rulesIter);
                assert(ruleIndex < mGrammar.getRulesCount());
                if(rules.size() == 1)
                    return ruleIndex;

                rulesIter = rules.erase(rulesIter);
            }
        }

        ++processedSymbols;
    }

    return ruleIndex;
}

size_t ParserInstance::getSubsentenceMaxRuleLevel(size_t beginPosition) const
{
    size_t maxLevel = 0;
    size_t position = beginPosition;
    size_t ruleIndex = 0;
    while(position < mParsedSentence.size())
    {
        ruleIndex = getRule(position);
        if(ruleIndex < mGrammar.getRulesCount())
        {
            if(getRuleLevel(ruleIndex) > maxLevel)
                maxLevel = getRuleLevel(ruleIndex);

            position += mGrammar.getRule(ruleIndex).getBodyLength();
        }
        else
        {
            ++position;
        }
    }

    return maxLevel;
}

size_t ParserInstance::getSubsentenceMaxSymbolLevel(size_t beginPosition) const
{
    return getSubsentenceMaxSymbolLevel(beginPosition, mParsedSentence.size() -
            beginPosition);
}

size_t ParserInstance::getSubsentenceMaxSymbolLevel(size_t beginPosition,
        size_t symbols) const
{
    size_t maxLevel = 0;
    size_t position = beginPosition;
    while(position < mParsedSentence.size() &&
            position - beginPosition < symbols)
    {
        if(mGrammar.getSymbolLevel(mParsedSentence[position]) > maxLevel)
            maxLevel = mGrammar.getSymbolLevel(mParsedSentence[position]);

        ++position;
    }

    return maxLevel;
}

const ParserInstance::Rules ParserInstance::getRules(const Symbol &symbol) const
{
    Rules rules;
    for(size_t i = 0; i < mGrammar.getRulesCount(); ++i)
        if(mGrammar.getRule(i).getBody(0) == symbol)
            rules.push_back(mGrammar.getRule(i));
    return rules;
}

const ParserInstance::Rules ParserInstance::getRules(const Symbol &symbol,
        size_t level) const
{
    Rules rules;
    for(size_t i = 0; i < mGrammar.getRulesCount(); ++i)
        if(mGrammar.getRule(i).getBody(0) == symbol &&
                getRuleLevel(i) >= level)
            rules.push_back(mGrammar.getRule(i));
    return rules;
}

size_t ParserInstance::getRuleLevel(size_t ruleIndex) const
{
    return mGrammar.getRuleLevel(ruleIndex);
}

size_t ParserInstance::getRuleIndex(const Rule &rule) const
{
    size_t i = 0;
    for(; i < mGrammar.getRulesCount(); ++i)
        if(mGrammar.getRule(i) == rule)
            return i;
    return i;
}

void ParserInstance::rewriteBodyWithHead(size_t position, size_t ruleIndex)
{
    assert(position < mParsedSentence.size());
    assert(ruleIndex < mGrammar.getRulesCount());

    mParsedSentence.erase(mParsedSentence.begin() +
            position,
            mParsedSentence.begin() + position +
            mGrammar.getRule(ruleIndex).getBodyLength());
    mParsedSentence.insert(mParsedSentence.begin() +
            position,
            mGrammar.getRule(ruleIndex).getHead());
}

void ParserInstance::processRewrite(size_t, size_t)
{
}
}
