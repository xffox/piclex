#include "ParserInstance.h"

#include <cassert>

#include "Logger.h"
#include "BaseExceptions.h"

using namespace base;

namespace search
{
ParserInstance::ParserInstance(const Grammar &grammar,
        const std::string &str)
    :mGrammar(grammar), mStr(sentence(str))
    ,mValid(false)
    ,mStrPosition(0)
{
}

ParserInstance::~ParserInstance()
{
}

bool ParserInstance::isValid() const
{
    return mValid;
}

void ParserInstance::parse()
{
    if( (mValid = process()) )
        rewrite();
}

void ParserInstance::rewrite()
{
}

bool ParserInstance::process()
{
    Log().debug("parse %s", makeString(mStr).c_str());

    Grammar::Rules rules = getRules(mGrammar.getStartSymbol());
    addStates(rules, mStrPosition);

    bool newStateAdded = false;
    Log().debug("position: %lu", mStrPosition);
    while(mStrPosition <= mStr.size() && mStrPosition < mStatesQueue.size())
    {

        newStateAdded = false;

//        States::const_iterator iter = mStatesQueue[mStrPosition].begin();
        States states = mStatesQueue[mStrPosition];
        size_t i = 0;
//        for(; iter != mStatesQueue[mStrPosition].end(); ++iter)
        for(; i < states.size(); ++i)
        {
//            if(iter->isFinished())
            if(states[i].isFinished())
            {
//                States::const_iterator prevIter =
//                    mStatesQueue[iter->getOriginPosition()].begin();
//                States::const_iterator prevIter =
//                    mStatesQueue[states[i].getOriginPosition()].begin();
//                for(; prevIter != mStatesQueue[iter->getOriginPosition()].end();
//                        ++prevIter)
                States prevStates = mStatesQueue[states[i].getOriginPosition()];
                size_t j = 0;
//                for(; prevIter != 
//                        mStatesQueue[states[i].getOriginPosition()].end();
//                        ++prevIter)
                for(; j < prevStates.size(); ++j)
                {
//                    if(prevIter->getNext() == iter->getHead())
                    if(!prevStates[j].isFinished() &&
                            prevStates[j].getNext() == states[i].getHead())
                    {
//                        State state(*prevIter);
                        State state(prevStates[j]);
                        state.shift(mStrPosition);
                        if(addState(state, mStrPosition))
                        {
                            newStateAdded = true;
                        }
                    }
                }
            }
//            else if(iter->getNext() == mStr[mStrPosition])
            else if(mStrPosition < mStr.size() &&
                    states[i].getNext() == mStr[mStrPosition])
            {
//                State state(*iter);
                State state(states[i]);
                state.shift(mStrPosition + 1);
                addState(state, mStrPosition + 1);
            }
            else
            {
//                rules = getRules(iter->getNext());
                rules = getRules(states[i].getNext());
                if(addStates(rules, mStrPosition))
                    newStateAdded = true;
            }
        }

        //TODO: check if need this
        if(!newStateAdded)
        {
            ++mStrPosition;
            Log().debug("position: %lu", mStrPosition);
        }
    }

    bool valid = false;
    if(mStatesQueue.size() > 0 && mStatesQueue.size() == mStr.size() + 1)
    {
        States::const_iterator iter = mStatesQueue.back().begin();
        for(; iter != mStatesQueue.back().end(); ++iter)
            if(iter->getHead() == mGrammar.getStartSymbol())
                if(iter->isFinished())
                    valid = true;
    }

    Log().debug("str %s", valid?"valid":"invalid");

    return valid;
}

size_t ParserInstance::getRuleIndex(const Rule &rule) const
{
    size_t i = 0;
    for(; i < mGrammar.getRulesCount(); ++i)
        if(mGrammar.getRule(i) == rule)
            return i;
    return i;
}

Grammar::Rules ParserInstance::getRules(const Symbol &head) const
{
    Grammar::Rules rules;
    Grammar::Rules::const_iterator iter = mGrammar.getRules().begin();
    for(; iter != mGrammar.getRules().end(); ++iter)
        if(iter->getHead() == head)
            rules.push_back(*iter);
    return rules;
}

size_t ParserInstance::addStates(const Grammar::Rules &rules,
        size_t position)
{
    size_t newStatesCount = 0;
    Grammar::Rules::const_iterator iter = rules.begin();
    for(; iter != rules.end(); ++iter)
    {
        State state(*iter, position);
        if(addState(state, position))
            ++newStatesCount;
    }

    return newStatesCount;
}

bool ParserInstance::addState(const ParserInstance::State &state,
        size_t position)
{
    assert(mStatesQueue.size() >= position);

    if(mStatesQueue.size() == position)
        mStatesQueue.push_back(States());

    States::const_iterator iter = mStatesQueue[position].begin();
    States::const_iterator endIter = mStatesQueue[position].end();
    for(; iter != endIter; ++iter)
        if(*iter == state)
            return false;
    mStatesQueue[position].push_back(state);
    Log().debug("add state at %lu: %s -> %s, %lu %lu", position,
            makeString(state.getHead()).c_str(),
            makeString(state.getRule().getRuleBody()).insert(
                3*state.getRulePosition(), "*").c_str(),
            state.getOriginPosition(),
            state.getCompletePosition());
    return true;
}

ParserInstance::State::State(const Rule &rule, size_t originPosition)
    :mRule(rule), mRulePosition(0), mOriginPosition(originPosition)
    ,mCompletePosition(0)
{
}

const Symbol &ParserInstance::State::getHead() const
{
    return mRule.getHead();
}

const Rule &ParserInstance::State::getRule() const
{
    return mRule;
}

size_t ParserInstance::State::getRulePosition() const
{
    return mRulePosition;
}

size_t ParserInstance::State::getOriginPosition() const
{
    return mOriginPosition;
}

size_t ParserInstance::State::getCompletePosition() const
{
    return mCompletePosition;
}

const Symbol &ParserInstance::State::getNext() const
{
    if(mRulePosition < mRule.getBodyLength())
        return mRule.getBody(mRulePosition);
    throw base::OutOfBoundError(mRulePosition, mRule.getBodyLength());
}

void ParserInstance::State::shift(size_t strPosition)
{
    if(mRulePosition < mRule.getBodyLength())
    {
        ++mRulePosition;
        if(mRulePosition == mRule.getBodyLength())
            mCompletePosition = strPosition;
    }
    else
    {
        throw base::OutOfBoundError(mRulePosition, mRule.getBodyLength());
    }
}

bool ParserInstance::State::isFinished() const
{
    return mRulePosition == mRule.getBodyLength();
}

bool operator==(const ParserInstance::State &left,
        const ParserInstance::State &right)
{
    return left.getRule() == right.getRule() &&
        left.getRulePosition() == right.getRulePosition() &&
        left.getOriginPosition() == right.getOriginPosition() &&
        left.getCompletePosition() == right.getCompletePosition();
}

}
