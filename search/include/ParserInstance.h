#ifndef PARSE_INSTANCE_H
#define PARSE_INSTANCE_H

#include <vector>
#include <list>

#include "Grammar.h"

namespace search
{
class ParserInstance
{
public:
    class State
    {
    public:
        State(const Rule &rule, size_t originPosition);

        const Symbol &getHead() const;
        const Rule &getRule() const;

        size_t getRulePosition() const;

        size_t getOriginPosition() const;
        size_t getCompletePosition() const;

        const Symbol &getNext() const;
        void shift(size_t strPosition);
        bool isFinished() const;

    private:
        Rule mRule;
        size_t mRulePosition;
        size_t mOriginPosition;
        size_t mCompletePosition;
    };

    typedef std::vector<State> States;

public:
    ParserInstance(const Grammar &grammar, const std::string &str);
    virtual ~ParserInstance();

    void parse();

    bool isValid() const;

    const Grammar &getGrammar() const
    {
        return mGrammar;
    }

    const Sentence &getStr() const
    {
        return mStr;
    }

protected:
    const std::vector<States> &getStatesQueue() const
    {
        return mStatesQueue;
    }

private:
    virtual void rewrite();
    bool process();

    size_t getRuleIndex(const Rule &rule) const;
    Grammar::Rules getRules(const Symbol &head) const;

    size_t addStates(const Grammar::Rules &rules, size_t position);
    bool addState(const State &state, size_t position);

private:
    Grammar mGrammar;
    Sentence mStr;

    bool mValid;

    std::vector<States> mStatesQueue;
    size_t mStrPosition;
};

bool operator==(const ParserInstance::State &left,
        const ParserInstance::State &right);

}

#endif//PARSE_INSTANCE_H
