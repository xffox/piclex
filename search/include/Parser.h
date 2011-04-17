#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Grammar.h"

namespace search
{
class Parser
{
public:
    Parser(const Grammar &grammar);
    virtual ~Parser();

    virtual bool parse(const std::string &str) const;

private:
    Grammar mGrammar;
};
}

#endif//PARSER_H
