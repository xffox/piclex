#include "Parser.h"

#include "ParserInstance.h"

namespace search
{
Parser::Parser(const Grammar &grammar)
    :mGrammar(grammar)
{

}

Parser::~Parser()
{
}

bool Parser::parse(const std::string &str) const
{
    ParserInstance instance(mGrammar, str);
    instance.parse();
    return instance.isValid();
}
}
