#ifndef PARSE_INSTANCE_H
#define PARSE_INSTANCE_H

#include <vector>
#include <list>
#include <map>

#include "Grammar.h"

namespace search
{
class ParserInstance
{
    typedef std::vector<Rule> Rules;

public:
    ParserInstance(const Grammar &grammar, const std::string &str);
    virtual ~ParserInstance();

    bool isValid() const;

protected:
    const Sentence &getParsedSentence() const
    {
        return mParsedSentence;
    }

    const Grammar &getGrammar() const
    {
        return mGrammar;
    }

    const Sentence &getStr() const
    {
        return mStr;
    }

private:
    virtual void processRewrite(size_t position, size_t ruleIndex);

    bool parse();

    bool process();
    size_t process(size_t position);

    void rewriteBodyWithHead(size_t position, size_t ruleIndex);

    size_t getSubsentenceMaxRuleLevel(size_t beginPosition) const;
    size_t getSubsentenceMaxSymbolLevel(size_t beginPosition) const;
    size_t getSubsentenceMaxSymbolLevel(size_t beginPosition,
            size_t symbols) const;

    size_t getRule(size_t position) const;
    const Rules getRules(const Symbol &symbol) const;
    const Rules getRules(const Symbol &symbol,
            size_t level) const;

    size_t getRuleLevel(size_t ruleIndex) const;

    size_t getRuleIndex(const Rule &rule) const;

private:
    Sentence mParsedSentence;

    Grammar mGrammar;
    Sentence mStr;

    bool mValid;
};
}

#endif//PARSE_INSTANCE_H
