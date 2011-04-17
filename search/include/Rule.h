#ifndef RULE_H
#define RULE_H

#include "Symbol.h"
#include "Sentence.h"

namespace search
{
class Rule
{
public:
    Rule(const Symbol &head, const Sentence &body);

    bool operator==(const Rule &that) const;
    bool operator!=(const Rule &that) const;

    const Symbol &getHead() const;
    //TODO: rename
    const Symbol &getBody(size_t index) const;
    const Sentence &getRuleBody() const;
    size_t getBodyLength() const;

private:
    Symbol mHead;
    Sentence mBody;
};
}

#endif//RULE_H
