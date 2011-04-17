#ifndef TREE_BUILDER_PARSER_INSTANCE_H
#define TREE_BUILDER_PARSER_INSTANCE_H

#include "ParserInstance.h"

namespace search
{

class TreeBuilderParserInstance: public ParserInstance
{
public:
    TreeBuilderParserInstance(const Grammar &grammar, const std::string &str);
    virtual ~TreeBuilderParserInstance();

private:
    virtual void processRewrite(size_t position, size_t ruleIndex);
};

}

#endif//TREE_BUILDER_PARSER_INSTANCE_H
