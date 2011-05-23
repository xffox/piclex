#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <list>

#include "Grammar.h"

namespace search
{
class Parser
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
    Parser();
    Parser(const Grammar &grammar);
    virtual ~Parser();

    bool parse(const std::string &str);

    bool isValid() const;

    const Grammar &getGrammar() const
    {
        return mGrammar;
    }

    const Sentence &getStr() const
    {
        return mStr;
    }

    void setGrammar(const Grammar &grammar);

protected:
    const std::vector<States> &getStatesQueue() const
    {
        return mStatesQueue;
    }

private:
    void parse();

    virtual void rewrite();
    virtual void resetRewrite();

    bool process();

    size_t getRuleIndex(const Rule &rule) const;
    Grammar::Rules getRules(const Symbol &head) const;

    size_t addStates(const Grammar::Rules &rules, size_t position);
    bool addState(const State &state, size_t position);

    void reset();

private:
    Grammar mGrammar;
    Sentence mStr;

    bool mValid;

    std::vector<States> mStatesQueue;
    size_t mStrPosition;
};

bool operator==(const Parser::State &left,
        const Parser::State &right);

}

#endif//PARSER_H
